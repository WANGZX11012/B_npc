#!/usr/bin/env python3
"""把 NPC 的 [perf] 日志变成一份可读报告 + 一行 CSV。

用法:
    perf_report.py <perf.log>           # 可读报告 + CSV 行
    perf_report.py <perf.log> --csv     # 只打印 CSV 行(追加到 perf.csv 用)

正则必须跟着 vsrc/perf.v 的 $display 走:
    [perf] Total insts : N        ← 冒号前有空格
    [perf] ifu  ev=N (总线事务) cyc=M  miss=K (块级)
    [perf] lsu  ev=N (访存次数)     cyc=M
    [perf] alu   insts=N cycles=M cpi=x.xx    ← 是等号, 不是冒号
"""
import re
import subprocess
import sys

path = sys.argv[1] if len(sys.argv) > 1 else "build/perf.log"
csv_only = "--csv" in sys.argv

log = open(path, encoding="utf-8", errors="ignore").read()


def g(pat, default=None):
    m = re.search(pat, log)
    return default if m is None else int(m.group(1))


# ── 抓数 ──
insts = g(r"Total insts\s*:\s*(\d+)")
cycles = g(r"Total cycles\s*:\s*(\d+)")
if not insts or not cycles:
    print("!! 日志里没有 [perf] 输出, 确认 CONFIG_PERF=y", file=sys.stderr)
    sys.exit(1)

# ev 与 cyc 之间可能夹着说明文字, 用 .*? 跨过去
ifu_ev = g(r"ifu\s+ev=(\d+)", 0)
ifu_cy = g(r"ifu\s+ev=\d+\b.*?cyc=(\d+)", 0)
lsu_ev = g(r"lsu\s+ev=(\d+)", 0)
lsu_cy = g(r"lsu\s+ev=\d+\b.*?cyc=(\d+)", 0)
miss_n = g(r"miss_n=(\d+)", 0)

# 分类行用的是 "insts=" / "cycles="; br 打印成 "br"
CATS = ["alu", "lui", "load", "store", "br", "jmp", "csr", "sys"]
mix = []
for n in CATS:
    c = g(rf"{n}\s+insts=(\d+)", 0)
    y = g(rf"{n}\s+insts=\d+\s+cycles=(\d+)", 0)
    if c:
        mix.append((n, c, y))
mix.sort(key=lambda x: -x[1])

cat_n = {n: c for n, c, _ in mix}

cpi = cycles / insts
ipc = insts / cycles
other = cycles - ifu_cy - lsu_cy

try:
    commit = subprocess.check_output(
        ["git", "rev-parse", "--short", "HEAD"],
        stderr=subprocess.DEVNULL,
    ).decode().strip()
except Exception:
    commit = "nogit"


def pct(x, t):
    return f"{100.0 * x / t:.1f}%" if t else "?"


def per(x, t):
    return f"{x / t:.2f}" if t else "?"


# ── 模式 1: 只输出 CSV 行 ──
if csv_only:
    print(",".join(str(v) for v in [
        commit, insts, cycles, f"{cpi:.2f}", f"{ipc:.4f}",
        ifu_ev, f"{100.0 * ifu_cy / cycles:.1f}",
        lsu_ev, f"{100.0 * lsu_cy / cycles:.1f}",
        cat_n.get("alu", 0), cat_n.get("load", 0), cat_n.get("store", 0),
    ]))
    sys.exit(0)

# ── 模式 2: 人读报告 ──
L = "─" * 62
print(L)
print(f"  NPC Performance Report                     commit {commit}")
print(L)
print(f"  {'Instructions':<14}{insts:>16,}")
print(f"  {'Cycles':<14}{cycles:>16,}")
print(f"  {'CPI':<14}{cpi:>16.2f}")
print(f"  {'IPC':<14}{ipc:>16.4f}")
print(L)
print(f"  {'PHASE':<12}{'cycles':>13}{'share':>9}{'cyc/inst':>10}")
for label, cy in (("fetch", ifu_cy), ("memory", lsu_cy), ("other", other)):
    print(f"  {label:<12}{cy:>13,}{pct(cy, cycles):>9}{per(cy, insts):>10}")
print(L)
print(f"  {'INSTRUCTION':<12}{'count':>13}{'share':>9}{'CPI':>10}")
for n, c, y in mix:
    print(f"  {n:<12}{c:>13,}{pct(c, insts):>9}{y / c:>10.2f}")
print(L)
