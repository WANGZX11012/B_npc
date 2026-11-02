#!/bin/sh
# baseline.sh — B5 流水线改造的回归基线
NPC=/home/wang/ysyx-workbench/npc
AM=/home/wang/ysyx-workbench/am-kernels

cd "$NPC" || exit 1

runcase() {
  f="$1"
  label="${2:-$(basename "$f" .bin)}"
  printf "[%s] %-22s " "$(date +%H:%M:%S)" "$label"
  if [ ! -f "$f" ]; then
    echo "MISSING"
    return
  fi
  out=$(./build/Vtop -b "$f" </dev/null 2>&1)
  t=$(echo "$out" | grep -oE "HIT GOOD TRAP|HIT BAD TRAP" | tail -1)
  i=$(echo "$out" | grep -oE "total_inst = [0-9]+" | tail -1)
  if [ -z "$t" ]; then
    echo "NO_RESULT"
    echo "$out" | tail -3 | sed 's/^/        /'
    return
  fi
  echo "$t  $i"
}

echo "===== cpu-tests (独立 bin, 不需要 mainargs) ====="
for x in add add-longlong bit bubble-sort crc32 div dummy load-store hello-str; do
  runcase "$AM/tests/cpu-tests/build/$x-riscv32-npc.bin"
done



echo "===== microbench test ====="
MB="$AM/benchmarks/microbench"
( cd "$MB" && make ARCH=riscv32-npc mainargs=test insert-arg >/dev/null 2>&1 )
runcase "$MB/build/microbench-riscv32-npc.bin"
