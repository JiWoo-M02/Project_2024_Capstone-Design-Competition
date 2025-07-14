# ifndef TRAFFIC_LIGHT_H
# define TRAFFIC_LIGHT_H

# include "Pin_Definitions.h"

// 차량 신호등 상태 설정 함수
void setLightState(int lightNumber, int green, int yellow, int red) {
  switch (lightNumber) {
    case 1:
      digitalWrite(2, red);    // 1번 차량 신호등 빨간불
      digitalWrite(3, yellow); // 1번 차량 신호등 노란불
      digitalWrite(4, green);  // 1번 차량 신호등 초록불
      break;
    case 2:
      digitalWrite(5, red);    // 2번 차량 신호등 빨간불
      digitalWrite(6, yellow); // 2번 차량 신호등 노란불
      digitalWrite(7, green);  // 2번 차량 신호등 초록불
      break;
    case 3:
      digitalWrite(8, red);    // 3번 차량 신호등 빨간불
      digitalWrite(9, yellow); // 3번 차량 신호등 노란불
      digitalWrite(10, green); // 3번 차량 신호등 초록불
      break;
    case 4:
      digitalWrite(11, red);   // 4번 차량 신호등 빨간불
      digitalWrite(12, yellow);// 4번 차량 신호등 노란불
      digitalWrite(13, green); // 4번 차량 신호등 초록불
      break;
  }
}

// 보행자 신호등 상태 설정 함수
void setPedestrianState(int lightNumber, int red, int green) {
  switch (lightNumber) {
    case 1:
      digitalWrite(14, red);   // 보행자 1번 신호등 빨간불
      digitalWrite(15, green); // 보행자 1번 신호등 초록불
      break;
    case 2:
      digitalWrite(16, red);   // 보행자 2번 신호등 빨간불
      digitalWrite(17, green); // 보행자 2번 신호등 초록불
      break;
    case 3:
      digitalWrite(18, red);   // 보행자 3번 신호등 빨간불
      digitalWrite(19, green); // 보행자 3번 신호등 초록불
      break;
    case 4:
      digitalWrite(20, red);   // 보행자 4번 신호등 빨간불
      digitalWrite(21, green); // 보행자 4번 신호등 초록불
      break;
  }
}

// 보행자 신호등만 모두 빨간불로 설정
void setAllPedestrianRed() {
  for (int i = 1; i <= 4; i++) {
    setPedestrianState(i, HIGH, LOW); // 모든 보행자 신호등 빨간불
  }
}

// 나머지 신호등을 모두 빨간불로 설정하는 함수
void setAllRedExcept(int activeLight) {
  for (int i = 1; i <= 4; i++) {
    if (i != activeLight) {
      setLightState(i, LOW, LOW, HIGH); // 차량 신호등: 활성화된 신호등을 제외하고 모두 빨간불
      setPedestrianState(i, HIGH, LOW); // 보행자 신호등: 활성화된 신호등을 제외하고 모두 빨간불
    }
  }
}

void blinkYellowLights() {
  static bool yellowOn = false;
  static unsigned long lastBlinkTime = 0;
  unsigned long currentMillis = millis();

  if (currentMillis - lastBlinkTime >= 500) { // 500ms마다 깜빡임
    yellowOn = !yellowOn;
    lastBlinkTime = currentMillis;
  }

  int yellowState = yellowOn ? HIGH : LOW;

  // 모든 신호등에 대해 빨간불을 끔
  digitalWrite(eastCledRed, LOW);
  digitalWrite(westCledRed, LOW);
  digitalWrite(southCledRed, LOW);
  digitalWrite(northCledRed, LOW);

  // 모든 신호등에 대해 초록불을 끔
  digitalWrite(eastCledGreen, LOW);
  digitalWrite(westCledGreen, LOW);
  digitalWrite(southCledGreen, LOW);
  digitalWrite(northCledGreen, LOW);

  // 모든 차량 신호등에 대해 노란불 깜빡임 설정
  digitalWrite(eastCledOrange, yellowState);
  digitalWrite(westCledOrange, yellowState);
  digitalWrite(southCledOrange, yellowState);
  digitalWrite(northCledOrange, yellowState);
}

// 모든 차량 신호등 끄기
void setAllVehicleLightsOff() {
  digitalWrite(eastCledRed, LOW);
  digitalWrite(eastCledOrange, LOW);
  digitalWrite(eastCledGreen, LOW);
  digitalWrite(westCledRed, LOW);
  digitalWrite(westCledOrange, LOW);
  digitalWrite(westCledGreen, LOW);
  digitalWrite(southCledRed, LOW);
  digitalWrite(southCledOrange, LOW);
  digitalWrite(southCledGreen, LOW);
  digitalWrite(northCledRed, LOW);
  digitalWrite(northCledOrange, LOW);
  digitalWrite(northCledGreen, LOW);
}

// 모든 보행자 신호등 끄기
void setAllPedestrianLightsOff() {
  digitalWrite(eastPledRed, LOW);
  digitalWrite(eastPledGreen, LOW);
  digitalWrite(westPledRed, LOW);
  digitalWrite(westPledGreen, LOW);
  digitalWrite(southPledRed, LOW);
  digitalWrite(southPledGreen, LOW);
  digitalWrite(northPledRed, LOW);
  digitalWrite(northPledGreen, LOW);
}

#endif
