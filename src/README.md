# AP

### **1. Listener (입력 이벤트 감지)**  
- **주요 파일**: `Listener.c`, `Listener.h`  
- **기능**:
  - 버튼 입력 및 UART 명령을 감지하여 이벤트를 처리.
  - 버튼 이벤트에 따라 팬 상태(FanState) 및 타이머 상태(TimerState)를 변경.
  - UART를 통해 팬과 타이머 상태를 설정하는 명령을 처리.  

### **2. Presenter (출력 표시 및 팬 속도 관리)**  
- **주요 파일**: `Presenter.c`, `Presenter.h`  
- **기능**:
  - 팬 상태와 타이머 데이터를 LCD 및 FND에 표시.
  - 팬 속도를 상태에 따라 조절.
  - 자동(AUTO) 모드일 경우 팬 속도를 랜덤으로 조정.  

### **3. Service (팬 상태 및 타이머 계산)**  
- **주요 파일**: `Service_DigitalFan.c`, `Service_DigitalFan.h`  
- **기능**:
  - 타이머 데이터를 계산하여 팬 상태를 제어.
  - AUTO 모드일 때 팬 상태를 랜덤으로 변경.
  - UART 명령을 통해 타이머를 설정.  

### **4. Main (전체 시스템 초기화 및 실행)**  
- **주요 파일**: `apMain.c`, `apMain.h`  
- **기능**:
  - 시스템의 주요 모듈(Listener, Presenter, Service)을 초기화.
  - 주기적으로 입력 감지, 팬 동작, 타이머 계산 실행.  

### **작동 원리**  

1. **초기화**:  
   `apMain_init()` 함수에서 모든 모듈과 타이머를 초기화하고 인터럽트를 활성화.  

2. **입력 처리**:  
   - `Listener_eventCheck()` 함수에서 버튼과 UART 입력을 감지.
   - 버튼 상태에 따라 팬과 타이머 상태를 업데이트.  

3. **타이머 계산**:  
   - `DigitalFan_Timecalc()` 함수에서 타이머 값을 감소.
   - 타이머가 종료되면 팬을 OFF 상태로 전환.  

4. **출력 표시**:  
   - `Presenter_dispTimeData()` 함수에서 LCD와 FND에 현재 상태를 표시.
   - 팬 상태에 따라 LCD 게이지 표시.  

5. **팬 동작 제어**:  
   - `Presenter_FanData()`에서 팬의 속도를 설정.
   - AUTO 모드일 경우 랜덤한 속도로 팬 작동.  


### **인터럽트 구조**  

1. **USART0_RX_vect**:  
   UART 입력 데이터를 처리하여 팬 또는 타이머 상태 변경.  

2. **TIMER0_OVF_vect**:  
   FND 디스플레이 업데이트.  

3. **TIMER2_COMP_vect**:  
   타이머 및 AUTO 모드 계산.

# Driver
### **1. Button (버튼 입력 처리)**
- **주요 파일**: `button.c`, `button.h`
- **기능**:
  - 버튼 입력을 읽고 눌림(PUSHED) 및 뗌(RELEASED) 상태를 감지.
  - 노이즈를 방지하기 위해 `10ms` 지연 적용.
  - **주요 함수**:
    - `Button_init()`: 버튼 초기화.
    - `Button_GetState()`: 버튼 상태를 반환 (`ACT_PUSHED`, `ACT_RELEASED`, `ACT_NONE`).


### **2. Buzzer (버저 제어)**
- **주요 파일**: `Buzzer.c`, `Buzzer.h`
- **기능**:
  - 버튼 동작이나 팬 상태 변화 시 경고음을 생성.
  - 주파수(Hz)에 따라 다양한 톤을 출력.
  - **주요 함수**:
    - `Buzzer_init()`: 버저 초기화.
    - `Buzzer_makeHertz(hertz)`: 지정된 주파수로 소리 생성.
    - `Buzzer_buttonOn(hertz)`: 버튼 클릭 시 소리 재생.


### **3. Fan (팬 속도 제어)**
- **주요 파일**: `Fan.c`, `Fan.h`
- **기능**:
  - PWM 신호를 사용하여 팬의 속도를 조절.
  - **주요 함수**:
    - `Fan_init()`: 팬 관련 핀 초기화.
    - `Fan_speedMode(data)`: 속도에 따라 팬의 동작을 설정.


### **4. FND (FND 디스플레이 제어)**
- **주요 파일**: `FND.c`, `FND.h`
- **기능**:
  - 타이머 데이터를 4자리 숫자로 표시.
  - **주요 함수**:
    - `FND_init()`: FND 초기화.
    - `FND_dispNum(fndNum)`: 숫자를 FND에 표시.
    - `FND_colonOn() / FND_colonOff()`: 중앙 콜론 표시 조작.


### **5. LCD_I2C (LCD 디스플레이 제어)**
- **주요 파일**: `LCD_I2C.c`, `LCD_I2C.h`
- **기능**:
  - I2C 프로토콜을 통해 LCD와 통신.
  - 팬 속도 및 타이머 상태를 시각적으로 표시.
  - **주요 함수**:
    - `LCD_I2C_init()`: LCD 초기화.
    - `LCD_I2C_writeString(str)`: 문자열 출력.
    - `LCD_I2C_writeStringXY(row, col, str)`: 특정 좌표에 문자열 출력.
    - `LCD_Gauge_Low()`, `LCD_Gauge_middle()`, `LCD_Gauge_high()`: 팬 상태 게이지 표시.


### **시스템 통합 구조**

1. **Button → Listener**:
   - 버튼 입력은 `Listener` 모듈로 전달되어 이벤트를 처리.
   
2. **Listener → Service**:
   - 팬 상태 및 타이머 설정은 `Service` 모듈로 전달.
   
3. **Service → Presenter**:
   - 계산된 데이터를 `Presenter` 모듈로 전달하여 출력.
   
4. **Presenter → LCD/FND**:
   - LCD 및 FND를 통해 사용자에게 상태를 시각적으로 제공.

# Model
### **1. Model_FanState (팬 상태 관리)**

- **주요 파일**: `Model_FanState.c`, `Model_FanState.h`
- **기능**:
  - 팬 상태(FanState)를 저장하고 읽거나 업데이트하는 역할.
  - **팬 상태 값**:
    - `OFF`: 팬 꺼짐
    - `LOW`: 낮은 속도 (값: 5)
    - `MIDDLE`: 중간 속도 (값: 2)
    - `HIGH`: 높은 속도 (값: 1)
    - `AUTO`: 자동 모드 (값: 6)
- **주요 함수**:
  - `Model_getFanStateData()`: 현재 팬 상태를 반환.
  - `Model_setFanStateData(state)`: 팬 상태를 설정.


### **2. Model_TimerState (타이머 상태 관리)**

- **주요 파일**: `Model_TimerState.c`, `Model_TimerState.h`
- **기능**:
  - 타이머 상태(TimerState)와 UART 기반 타이머 명령 상태(TimerUartState)를 관리.
  - **타이머 상태 값**:
    - `NONE`: 타이머 없음
    - `THREE`: 3분 타이머
    - `FIVE`: 5분 타이머
    - `SEVEN`: 7분 타이머
- **주요 함수**:
  - `Model_getTimerStateData()`: 현재 타이머 상태를 반환.
  - `Model_setTimerStateData(state)`: 타이머 상태를 설정.
  - `Model_getTimerUartStateData()`: UART 타이머 명령 상태를 반환.
  - `Model_setTimerUartStateData(state)`: UART 타이머 명령 상태를 설정.


### **Model 모듈의 역할**
- **상태 저장소**:
  - 팬 및 타이머의 현재 상태를 시스템의 다른 모듈이 참조하거나 업데이트할 수 있도록 저장.
- **데이터의 중심화**:
  - 상태 데이터를 한 곳에서 관리하여 모듈 간 데이터 교환을 단순화.
- **시스템과의 연계**:
  - `Listener`, `Service`, `Presenter` 모듈에서 상태 데이터를 읽거나 업데이트하여 제어 로직 구현.


### **전체 시스템에서의 Model의 위치**
- **Listener**:
  - 버튼 및 UART 입력 이벤트를 통해 상태를 업데이트.
- **Service**:
  - 상태를 기반으로 타이머 계산 및 팬 제어 수행.
- **Presenter**:
  - 상태 데이터를 읽어 LCD 및 FND에 표시.

# Periph
### **1. GPIO (일반 입출력 핀 제어)**
- **주요 파일**: `GPIO.c`, `GPIO.h`
- **기능**:
  - GPIO 핀과 포트를 초기화하고, 데이터를 읽거나 쓰는 기능 제공.
- **주요 함수**:
  - `Gpio_initPort(DDR, dir)`: 포트를 입력 또는 출력 모드로 설정.
  - `Gpio_initPin(DDR, dir, pinNum)`: 특정 핀을 입력 또는 출력 모드로 설정.
  - `Gpio_writePin(PORT, pinNum, state)`: 특정 핀에 값을 설정.
  - `Gpio_readPin(PIN, pinNum)`: 특정 핀의 상태를 읽음.


### **2. I2C (I2C 통신 프로토콜)**
- **주요 파일**: `I2C.c`, `I2C.h`
- **기능**:
  - I2C 프로토콜을 사용하여 LCD 등 장치와 통신.
  - 데이터 송신 및 제어 신호 전송 지원.
- **주요 함수**:
  - `I2C_init()`: I2C 초기화 (100kHz SCL 설정).
  - `I2C_txByte(SLA_W, data)`: 특정 슬레이브 주소로 데이터 전송.
  - `I2C_start()` 및 `I2C_stop()`: I2C 시작 및 종료 조건 전송.

### **3. TIM (타이머 및 PWM 제어)**
- **주요 파일**: `TIM.c`, `TIM.h`
- **기능**:
  - 타이머와 PWM을 설정하고 인터럽트를 처리.
  - 타이머 0, 1, 2, 3 각각의 역할이 정의됨.
- **타이머 역할**:
  - **TIM0**: FND 디스플레이용 1ms 오버플로 인터럽트.
  - **TIM1**: PWM 설정.
  - **TIM2**: 타이머 계산용 1ms 주기 CTC 모드.
  - **TIM3**: 팬 제어용 Fast PWM 모드.
- **주요 함수**:
  - `TIM0_init()`, `TIM1_init()`, `TIM2_init()`, `TIM3_init()`: 각각 타이머 초기화.


### **4. UART0 (UART 통신)**
- **주요 파일**: `UART0.c`, `UART0.h`
- **기능**:
  - UART0를 사용한 직렬 통신 처리.
  - 데이터 송수신 및 버퍼 관리.
- **주요 함수**:
  - `UART0_init()`: UART 초기화 (9600bps 설정).
  - `UART0_ISR_Process()`: UART 인터럽트 처리.
  - `UART0_Transmit(data)`, `UART0_Receive()`: 데이터 송수신.
  - `UART0_sendString(str)`: 문자열 전송.
  - `UART0_getRxFlag()`, `UART0_clearRxFlag()`: 수신 플래그 관리.


### **모듈 간 관계**

1. **GPIO**:
   - 버튼(`button.c`)과 팬(`Fan.c`) 등 하드웨어 초기화 및 제어에 사용.
2. **I2C**:
   - LCD 통신(`LCD_I2C.c`)에서 활용.
3. **TIM**:
   - 타이머 기반 동작(`Service_DigitalFan.c`) 및 FND 디스플레이(`FND.c`)에서 사용.
4. **UART0**:
   - 외부 명령 수신(`Listener_FanUARTEvent`)과 상태 업데이트에 활용.