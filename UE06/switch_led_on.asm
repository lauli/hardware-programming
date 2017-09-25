	.global switch_blue_led_on, switch_blue_led_off, listen_for_button_s1_press

	.text
P5_LED_DIR .word 0x40004C44
P5_LED_OUT .word 0x40004C42
P5_BTN_IN  .word 0x42098804	; bitmask address for J4.33

listen_for_button_s1_press:
	mov r0, #0				; reset r0
	ldr r1, P5_BTN_IN		; load pointer to r1
	ldrb r0, [r1]			; load a byte to r0

	cbnz r0, switch_blue_led_off		; check if r0 is not 0 -> button is not pressed
	b switch_blue_led_on

switch_blue_led_off:
	; disables the light on the RGB LED
	mov r0, #0				; save value for no color
	ldr r1, P5_LED_DIR		; load pointer to P5DIR in r1
	strb r0, [r1]			; store the value of r0 in the memory on address r1

	; write 0 to P5OUT (located at 0x40004C42) = turn off
	ldr r1, P5_LED_OUT		; load pointer to P5OUT in r1
	strb r0, [r1]			; store the value of r0 in the memory on address r1
	bx lr					; exit

switch_blue_led_on:
	; enables the blue light on the RGB LED
	mov r0, #0x40			; save value for blue (0x40) in r0
	ldr r1, P5_LED_DIR		; load pointer to P5DIR in r1
	strb r0, [r1]			; store the value of r0 in the memory on address r1

	; write 1 to P1OUT (located at 0x40004C42) = turn on
	ldr r1, P5_LED_OUT		; load pointer to P5OUT in r1
	strb r0, [r1]			; store the value of r0 in the memory on address r1
	bx lr					; exit
