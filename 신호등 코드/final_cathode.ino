# include "Pin_Definitions.h"
# include "segment.h"
# include "traffic_light.h"

const long greenLightDuration = 2000;  // 초록불 3초
const long yellowLightDuration = 1000; // 노란불 1초

unsigned long previousMillis = 0;
int currentLight = 1;  // 현재 초록불이 켜진 차량 신호등 (1번부터 시작)
int state;
int previousState = -1;  // 이전 상태를 저장할 변수

bool vehicleMode = false;  // 현재 "차량" 모드가 활성화되어 있는지 여부
bool pedestrianGreen = false;  // 보행자 신호등이 초록인지 여부를 추적

void setup() {
  // 차량 신호등 핀 설정
  pinMode(eastCledRed, OUTPUT);
  pinMode(eastCledOrange, OUTPUT);
  pinMode(eastCledGreen, OUTPUT);
  pinMode(westCledRed, OUTPUT);
  pinMode(westCledOrange, OUTPUT);
  pinMode(westCledGreen, OUTPUT);
  pinMode(southCledRed, OUTPUT);
  pinMode(southCledOrange, OUTPUT);
  pinMode(southCledGreen, OUTPUT);
  pinMode(northCledRed, OUTPUT);
  pinMode(northCledOrange, OUTPUT);
  pinMode(northCledGreen, OUTPUT);

  // 보행자 신호등 핀 설정
  pinMode(eastPledRed, OUTPUT);
  pinMode(eastPledGreen, OUTPUT);
  pinMode(westPledRed, OUTPUT);
  pinMode(westPledGreen, OUTPUT);
  pinMode(southPledRed, OUTPUT);
  pinMode(southPledGreen, OUTPUT);
  pinMode(northPledRed, OUTPUT);
  pinMode(northPledGreen, OUTPUT);

  // 7세그먼트 디스플레이 핀 설정
  pinMode(east_segA, OUTPUT);
  pinMode(east_segB, OUTPUT);
  pinMode(east_segC, OUTPUT);
  pinMode(east_segD, OUTPUT);
  pinMode(east_segE, OUTPUT);
  pinMode(east_segF, OUTPUT);
  pinMode(east_segG, OUTPUT);
  pinMode(west_segA, OUTPUT);
  pinMode(west_segB, OUTPUT);
  pinMode(west_segC, OUTPUT);
  pinMode(west_segD, OUTPUT);
  pinMode(west_segE, OUTPUT);
  pinMode(west_segF, OUTPUT);
  pinMode(west_segG, OUTPUT);
  pinMode(south_segA, OUTPUT);
  pinMode(south_segB, OUTPUT);
  pinMode(south_segC, OUTPUT);
  pinMode(south_segD, OUTPUT);
  pinMode(south_segE, OUTPUT);
  pinMode(south_segF, OUTPUT);
  pinMode(south_segG, OUTPUT);
  pinMode(north_segA, OUTPUT);
  pinMode(north_segB, OUTPUT);
  pinMode(north_segC, OUTPUT);
  pinMode(north_segD, OUTPUT);
  pinMode(north_segE, OUTPUT);
  pinMode(north_segF, OUTPUT);
  pinMode(north_segG, OUTPUT);

  Serial.begin(115200);

  // 초기 상태 설정
  setAllVehicleLightsOff();
  setAllPedestrianLightsOff();
}

void loop() {
  if (Serial.available() > 0) {
    int data = Serial.read();
    if (data >= '0' && data <= '9') {  // 유효한 숫자인지 확인
      int numericValue = data - '0';   // ASCII 값을 숫자로 변환
      if (numericValue != previousState) {
        state = numericValue;
        previousState = state;  // 이전 상태를 갱신
        Serial.println(state);  // 상태를 출력
      }
    }
  } else {
    turnOffDisplay(1);
    turnOffDisplay(2);
    turnOffDisplay(3);
    turnOffDisplay(4);
    setAllPedestrianLightsOff();
    blinkYellowLights(); // 차량 신호등을 노란불로 깜빡이게 설정}

    unsigned long currentMillis = millis();
    unsigned long elapsedTime = currentMillis - previousMillis;
    turnOffDisplay(1);
    turnOffDisplay(2);
    turnOffDisplay(3);
    turnOffDisplay(4);
    resetDisplayForLight(currentLight, state, elapsedTime);
  }


  // 기본 모드 동작 (state == 0)
  if (state == 0) {
    unsigned long currentMillis = millis();  // currentMillis 변수 선언 및 초기화
    // 차량 또는 보행자 모드에서 전환되었을 때, 초기화
    if (currentMillis - previousMillis >= greenLightDuration) {
      // 기본 모드 동작
      setLightState(currentLight, HIGH, LOW, LOW);  // 현재 차량 신호등 초록불
      setPedestrianState(currentLight, LOW, HIGH);  // 현재 보행자 신호등 초록불
      setAllRedExcept(currentLight);

      // 현재 초록불 상태의 차량 신호등을 노란불로 전환
      setLightState(currentLight, LOW, HIGH, LOW);
      delay(yellowLightDuration);

      // 다음 신호등으로 전환
      int nextLight = (currentLight % 4) + 1;      // 다음 신호등 계산
      setLightState(currentLight, LOW, LOW, HIGH); // 현재 차량 신호등 빨간불
      setLightState(nextLight, HIGH, LOW, LOW);    // 다음 차량 신호등 초록불

      // 보행자 신호등 전환: 현재 보행자 신호등을 빨간불로 전환하고, 다음 보행자 신호등을 초록불로 전환
      setPedestrianState(currentLight, HIGH, LOW); // 현재 보행자 신호등 빨간불
      setPedestrianState(nextLight, LOW, HIGH);    // 다음 보행자 신호등 초록불

      // 현재 초록불 상태 업데이트
      currentLight = nextLight;
      previousMillis = millis();  // 새로운 초록불 지속 시간 시작
    }
  }

  // 차량 모드 동작 (state == 1)
  else if (state == 1) {
    unsigned long currentMillis = millis();  // currentMillis 변수 선언 및 초기화
    unsigned long elapsedTime = currentMillis - previousMillis;

    if (elapsedTime < 3000) {
      // 0~3초: 1번과 3번 차량 신호등 초록불
      setLightState(1, HIGH, LOW, LOW);  // 1번 차량 신호등 초록불
      setLightState(3, HIGH, LOW, LOW);  // 3번 차량 신호등 초록불
      setLightState(2, LOW, LOW, HIGH);  // 2번 차량 신호등 빨간불
      setLightState(4, LOW, LOW, HIGH);  // 4번 차량 신호등 빨간불
    } else if (elapsedTime < 4000) {
      // 3~4초: 1번과 3번 차량 신호등 노란불
      setLightState(1, LOW, HIGH, LOW);  // 1번 차량 신호등 노란불
      setLightState(3, LOW, HIGH, LOW);  // 3번 차량 신호등 노란불
    } else if (elapsedTime < 7000) {
      // 4~7초: 2번과 4번 차량 신호등 초록불
      setLightState(1, LOW, LOW, HIGH);  // 1번 차량 신호등 빨간불
      setLightState(3, LOW, LOW, HIGH);  // 3번 차량 신호등 빨간불
      setLightState(2, HIGH, LOW, LOW);  // 2번 차량 신호등 초록불
      setLightState(4, HIGH, LOW, LOW);  // 4번 차량 신호등 초록불
    } else if (elapsedTime < 8000) {
      // 7~8초: 2번과 4번 차량 신호등 노란불
      setLightState(2, LOW, HIGH, LOW);  // 2번 차량 신호등 노란불
      setLightState(4, LOW, HIGH, LOW);  // 4번 차량 신호등 노란불
    } else {
      // 8초 이후: 다음 주기 시작
      previousMillis = currentMillis;  // 타이머 초기화
      setLightState(1, HIGH, LOW, LOW);  // 1번 차량 신호등 초록불
      setLightState(3, HIGH, LOW, LOW);  // 3번 차량 신호등 초록불
      setLightState(2, LOW, LOW, HIGH);  // 2번 차량 신호등 빨간불
      setLightState(4, LOW, LOW, HIGH);  // 4번 차량 신호등 빨간불
    }

    // 보행자 신호등은 항상 빨간불로 유지
    setAllPedestrianRed();

  }
  // 휠체어 동작 (state == 2)
  else if (state == 2) {
    unsigned long currentMillis = millis();  // currentMillis 변수 선언 및 초기화
    unsigned long elapsedTime = currentMillis - previousMillis;

    if (elapsedTime < 8000) {
      // 0~8초: currentLight 차량 신호등과 보행자 신호등 초록불, 나머지 신호등 빨간불
      setLightState(currentLight, HIGH, LOW, LOW);   // currentLight 차량 신호등 초록불
      setPedestrianState(currentLight, LOW, HIGH);   // currentLight 보행자 신호등 초록불
      setAllRedExcept(currentLight);                 // 나머지 신호등 빨간불
    }
    else if (elapsedTime < 9000) {
      // 8~9초: currentLight 차량 신호등 노란불, 보행자 신호등은 변하지 않음
      setLightState(currentLight, LOW, HIGH, LOW);   // currentLight 차량 신호등 노란불
    }
    else {
      // 9초 이후: currentLight 차량 신호등과 보행자 신호등 빨간불, 다음 차량과 보행자 초록불
      setLightState(currentLight, LOW, LOW, HIGH);   // currentLight 차량 신호등 빨간불
      setPedestrianState(currentLight, HIGH, LOW);   // currentLight 보행자 신호등 빨간불

      // 다음 신호등으로 전환
      currentLight = (currentLight % 4) + 1;         // currentLight 순환 (1 -> 2 -> 3 -> 4)

      setLightState(currentLight, HIGH, LOW, LOW);   // nextLight 차량 신호등 초록불
      setPedestrianState(currentLight, LOW, HIGH);   // nextLight 보행자 신호등 초록불

      // 주기 종료 후 초기화
      previousMillis = currentMillis;     // 새로운 주기 시작
    }
  }
  else if (state == 3) {
    turnOffDisplay(1);
    turnOffDisplay(2);
    turnOffDisplay(3);
    turnOffDisplay(4);
    setAllPedestrianLightsOff();
    blinkYellowLights(); // 차량 신호등을 노란불로 깜빡이게 설정
  }
}
