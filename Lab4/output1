.data
_prompt: .asciiz "Enter an integer:"
_ret: .asciiz "\n"
.globl main
.text
read:
  li $v0, 4
  la $a0, _prompt
  syscall
  li $v0, 5
  syscall
  jr $ra

write:
  li $v0, 1
  syscall
  li $v0, 4
  la $a0, _ret
  syscall
  move $v0, $0
  jr $ra

main:
  move $fp, $sp
  addi $sp, $sp, -136
  li $t1, 0
  move $t0, $t1
  sw $t0, -4($fp)
  li $t1, 5
  move $t0, $t1
  sw $t0, -8($fp)
  lw $t1, -8($fp)
  move $t0, $t1
  sw $t0, -12($fp)
  lw $t1, -12($fp)
  move $t0, $t1
  sw $t0, -16($fp)
  lw $t1, -12($fp)
  move $t0, $t1
  sw $t0, -20($fp)
  lw $t1, -16($fp)
  lw $t2, -20($fp)
  mul $t0, $t1, $t2
  sw $t0, -24($fp)
  lw $t1, -12($fp)
  move $t0, $t1
  sw $t0, -28($fp)
  li $t1, 2
  move $t0, $t1
  sw $t0, -32($fp)
  lw $t1, -28($fp)
  lw $t2, -32($fp)
  add $t0, $t1, $t2
  sw $t0, -36($fp)
  lw $t1, -24($fp)
  lw $t2, -36($fp)
  mul $t0, $t1, $t2
  sw $t0, -40($fp)
  lw $t1, -40($fp)
  move $t0, $t1
  sw $t0, -44($fp)
  lw $t1, -44($fp)
  move $t0, $t1
  sw $t0, -48($fp)
  lw $t0, -48($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t1, -44($fp)
  move $t0, $t1
  sw $t0, -52($fp)
  lw $t1, -12($fp)
  move $t0, $t1
  sw $t0, -56($fp)
  lw $t1, -52($fp)
  lw $t2, -56($fp)
  div $t1, $t2
  mflo $t0
  sw $t0, -60($fp)
  li $t1, 1
  move $t0, $t1
  sw $t0, -64($fp)
  lw $t1, -60($fp)
  lw $t2, -64($fp)
  add $t0, $t1, $t2
  sw $t0, -68($fp)
  lw $t1, -68($fp)
  move $t0, $t1
  sw $t0, -72($fp)
  lw $t1, -72($fp)
  move $t0, $t1
  sw $t0, -76($fp)
  lw $t0, -76($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  lw $t1, -12($fp)
  move $t0, $t1
  sw $t0, -80($fp)
  lw $t1, -44($fp)
  move $t0, $t1
  sw $t0, -84($fp)
  lw $t1, -80($fp)
  lw $t2, -84($fp)
  add $t0, $t1, $t2
  sw $t0, -88($fp)
  lw $t1, -72($fp)
  move $t0, $t1
  sw $t0, -92($fp)
  li $t1, 3
  move $t0, $t1
  sw $t0, -96($fp)
  lw $t1, -92($fp)
  lw $t2, -96($fp)
  mul $t0, $t1, $t2
  sw $t0, -100($fp)
  lw $t1, -88($fp)
  lw $t2, -100($fp)
  sub $t0, $t1, $t2
  sw $t0, -104($fp)
  lw $t1, -44($fp)
  move $t0, $t1
  sw $t0, -108($fp)
  lw $t1, -12($fp)
  move $t0, $t1
  sw $t0, -112($fp)
  lw $t1, -108($fp)
  lw $t2, -112($fp)
  div $t1, $t2
  mflo $t0
  sw $t0, -116($fp)
  li $t1, 4
  move $t0, $t1
  sw $t0, -120($fp)
  lw $t1, -116($fp)
  lw $t2, -120($fp)
  sub $t0, $t1, $t2
  sw $t0, -124($fp)
  lw $t1, -104($fp)
  lw $t2, -124($fp)
  add $t0, $t1, $t2
  sw $t0, -128($fp)
  lw $t1, -128($fp)
  move $t0, $t1
  sw $t0, -4($fp)
  lw $t1, -4($fp)
  move $t0, $t1
  sw $t0, -132($fp)
  lw $t0, -132($fp)
  move $a0, $t0
  addi $sp, $sp, -4
  sw $ra, 0($sp)
  jal write
  lw $ra, 0($sp)
  addi $sp, $sp, 4
  li $t1, 0
  move $t0, $t1
  sw $t0, -136($fp)
  lw $t0, -136($fp)
  move $v0, $t0
  jr $ra
