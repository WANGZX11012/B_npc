// ============================================================================
// core_dbg.vh —— CPU 调试导出层 (DPI-C, 给 tb 的 difftest 用)
// ============================================================================

  export "DPI-C" function npc_dbg_pc;             // 下一条要取的 PC (= pc_reg)
  export "DPI-C" function npc_dbg_inst_pc;        // 当前这条指令自己的 PC (= ir_pc)
  export "DPI-C" function npc_dbg_retire;         // 这一拍退休了一条指令
  export "DPI-C" function npc_dbg_gpr;            // 第 i 个通用寄存器
  export "DPI-C" function npc_dbg_inst_retire;    // 干净状态 所有值都是执行完后的
  export "DPI-C" function npc_dbg_access_fault;  
  export "DPI-C" function npc_dbg_fault_addr;   

  function int npc_dbg_pc();              npc_dbg_pc      = pc;                         endfunction
  function int npc_dbg_inst_pc();         npc_dbg_inst_pc = ir_pc;                      endfunction
  function int npc_dbg_retire();          npc_dbg_retire  = {31'b0, retire};            endfunction
  function int npc_dbg_gpr(input int i);  npc_dbg_gpr     = u_regfile.rf[i];            endfunction
  function int npc_dbg_inst_retire();     npc_dbg_inst_retire  = {31'b0, inst_retire};  endfunction
  function int npc_dbg_access_fault();    npc_dbg_access_fault  = {31'b0, access_fault};  endfunction
  function int npc_dbg_fault_addr();     npc_dbg_fault_addr  = fault_addr_r;  endfunction
