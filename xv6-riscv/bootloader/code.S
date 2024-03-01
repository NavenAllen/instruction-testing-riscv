.global test_start

test_start:
    li a0, 0x000000FF    # Load immediate value 255 into register a0 (rs1)
    addi a0, a0, -1      # Add -1 to register a0, result stored back in a0 (rd = rs1 for simplicity
    sret

# RISCV has no HALT instruction, hence infinite looping to emulate HALT
test_end:
    j test_end

.global trap_vector
.align 4
trap_vector:
    j trap_vector

