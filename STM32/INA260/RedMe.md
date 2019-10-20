# INA260 �ߓd���ی�
### �v���W�F�N�g�ɒǉ����ׂ��t�@�C��
- INA260.h
- INA260.c
- pins.h
I2C�|�[�g�ƃA�h���X��`pins.h`���Œ�`

### �g����  

��  

```
printf("Who am I = %04x\n", ina260_who_am_i());

set_torquer_OCP(500.0);

uint16_t V, I;
V = get_torquer_voltage();
I = get_torquer_current();

float v, i;
v = get_torquer_voltage_f();
i = get_torquer_current_f();
printf("V = %6.2f[mV] I= %6.2f[mA]", v, i);

reset_torquer_OCP();
```

`set_torquer_OCP( current )`  
�ő�d����current[mA]�ɐݒ�  

`get_torquer_voltage()`  
`get_torquer_current()`  
���݂̓d���l�E�d���l�𐮐��l(���f�[�^)�Ŏ擾�B  
1LSB = 1.25mA �܂��� 1LSB = 1.25 mV�Ȃ̂ŁA1.25�{����ƒP�ʂ�mA,mV�ɂȂ�B  

`get_torquer_voltage_f()`  
`get_torquer_current_f()`  
���݂̓d���l�E�d���l��float�łŎ擾�B �P�ʂ�mA�܂���mV  

`reset_torquer_OCP()`  
�ߓd���ی�������B�֐��Ń��Z�b�g�����Ȃ������`set_torquer_OCP()`�Ŏw�肵���d���l��1�x������Ɠd���l���������Ȃ��Ă����̃A���[�g�s���̌x����Ԃ��p������B

### �A���[�g�s���̏�Ԃɂ���  
- �ʏ펞 �@�@LOW  
- �ߓd�����@ �n�C�C���s�[�_���X  
(INA260.c��ҏW���邱�ƂŕύX��)