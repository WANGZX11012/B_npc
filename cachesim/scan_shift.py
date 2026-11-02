#!/usr/bin/env python3
import subprocess, re

TRACE = "../build/itrace.bin"
BLK, NBLK = 16, 512

print(f"{'shift':>6} {'miss':>10} {'hit%':>9}")
rows = []
for off in range(0, 64, 4):          # 0,4,8,...,60 共 16 组
    r = subprocess.run(["./cachesim", TRACE, str(BLK), str(NBLK), str(off)],
                       capture_output=True, text=True)
    miss = int(re.search(r"miss=(\d+)",   r.stdout).group(1))
    acc  = int(re.search(r"access=(\d+)", r.stdout).group(1))
    print(f"{off:>6} {miss:>10} {100.0*(acc-miss)/acc:>8.2f}%")
    rows.append((off, miss))

print("\n--- 每 16 一组, 组内应完全相同 ---")
for base in range(0, 16, 4):
    same = [m for o, m in rows if o % 16 == base]
    print(f"mod16={base:>2}: {same}  {'OK' if len(set(same)) == 1 else 'DIFF!'}")
