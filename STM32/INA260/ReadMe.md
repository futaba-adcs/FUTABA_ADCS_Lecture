# INA260 過電流保護
### プロジェクトに追加すべきファイル
- INA260.h
- INA260.c
- pins.h
I2Cポートとアドレスは`pins.h`内で定義

### 使い方  

例  

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
最大電流をcurrent[mA]に設定  

`get_torquer_voltage()`  
`get_torquer_current()`  
現在の電流値・電圧値を整数値(生データ)で取得。  
1LSB = 1.25mA または 1LSB = 1.25 mVなので、1.25倍すると単位がmA,mVになる。  

`get_torquer_voltage_f()`  
`get_torquer_current_f()`  
現在の電流値・電圧値をfloatでで取得。 単位はmAまたはmV  

`reset_torquer_OCP()`  
過電流保護を解除。関数でリセットをしない限りは`set_torquer_OCP()`で指定した電流値を1度超えると電流値が小さくなってもこのアラートピンの警告状態が継続する。

### アラートピンの状態について  
- 通常時 　　LOW  
- 過電流時　 ハイインピーダンス  
(INA260.cを編集することで変更可)
