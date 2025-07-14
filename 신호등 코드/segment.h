# ifndef SEGMENT_H
# define SEGMENT_H

# include "Pin_Definitions.h"

// 7세그먼트에 표시할 숫자의 세그먼트 패턴
int numbers[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 1, 0, 1, 1}  // 9
};

// 7세그먼트 디스플레이를 끄는 함수 (캐소드 디스플레이용)
void turnOffDisplay(int lightNumber) {
  switch (lightNumber) {
    case 1:
      digitalWrite(east_segA, LOW);
      digitalWrite(east_segB, LOW);
      digitalWrite(east_segC, LOW);
      digitalWrite(east_segD, LOW);
      digitalWrite(east_segE, LOW);
      digitalWrite(east_segF, LOW);
      digitalWrite(east_segG, LOW);
      break;
    case 2:
      digitalWrite(west_segA, LOW);
      digitalWrite(west_segB, LOW);
      digitalWrite(west_segC, LOW);
      digitalWrite(west_segD, LOW);
      digitalWrite(west_segE, LOW);
      digitalWrite(west_segF, LOW);
      digitalWrite(west_segG, LOW);
      break;
    case 3:
      digitalWrite(south_segA, LOW);
      digitalWrite(south_segB, LOW);
      digitalWrite(south_segC, LOW);
      digitalWrite(south_segD, LOW);
      digitalWrite(south_segE, LOW);
      digitalWrite(south_segF, LOW);
      digitalWrite(south_segG, LOW);
      break;
    case 4:
      digitalWrite(north_segA, LOW);
      digitalWrite(north_segB, LOW);
      digitalWrite(north_segC, LOW);
      digitalWrite(north_segD, LOW);
      digitalWrite(north_segE, LOW);
      digitalWrite(north_segF, LOW);
      digitalWrite(north_segG, LOW);
      break;
  }
}

// 숫자를 7세그먼트 디스플레이에 표시하는 함수
void displayNumber(int lightNumber, int num) {
  switch (lightNumber) {
    case 1:
      digitalWrite(east_segA, numbers[num][0]);
      digitalWrite(east_segB, numbers[num][1]);
      digitalWrite(east_segC, numbers[num][2]);
      digitalWrite(east_segD, numbers[num][3]);
      digitalWrite(east_segE, numbers[num][4]);
      digitalWrite(east_segF, numbers[num][5]);
      digitalWrite(east_segG, numbers[num][6]);
      break;
    case 2:
      digitalWrite(west_segA, numbers[num][0]);
      digitalWrite(west_segB, numbers[num][1]);
      digitalWrite(west_segC, numbers[num][2]);
      digitalWrite(west_segD, numbers[num][3]);
      digitalWrite(west_segE, numbers[num][4]);
      digitalWrite(west_segF, numbers[num][5]);
      digitalWrite(west_segG, numbers[num][6]);
      break;
    case 3:
      digitalWrite(south_segA, numbers[num][0]);
      digitalWrite(south_segB, numbers[num][1]);
      digitalWrite(south_segC, numbers[num][2]);
      digitalWrite(south_segD, numbers[num][3]);
      digitalWrite(south_segE, numbers[num][4]);
      digitalWrite(south_segF, numbers[num][5]);
      digitalWrite(south_segG, numbers[num][6]);
      break;
    case 4:
      digitalWrite(north_segA, numbers[num][0]);
      digitalWrite(north_segB, numbers[num][1]);
      digitalWrite(north_segC, numbers[num][2]);
      digitalWrite(north_segD, numbers[num][3]);
      digitalWrite(north_segE, numbers[num][4]);
      digitalWrite(north_segF, numbers[num][5]);
      digitalWrite(north_segG, numbers[num][6]);
      break;
  }
}

// 디스플레이 초기화 및 제어 함수 (초록불이 켜질 때 호출)
void resetDisplayForLight(int lightNumber, int state, unsigned long elapsedTime) {
  int countdownTime;

  switch (state) {
    case 0:
      // 3초부터 1초까지 카운트다운 (state = 0)
      countdownTime = 3 - (elapsedTime / 1000); // 남은 시간 계산
      if (countdownTime >= 1 && countdownTime <= 3) {
        displayNumber(lightNumber, countdownTime); // 디스플레이에 남은 시간을 표시
      }
      break;

    case 1:
      // 디스플레이 OFF (state = 1)
      turnOffDisplay(lightNumber);
      break;

    case 2:
      // 9초부터 1초까지 카운트다운 (state = 2)
      countdownTime = 9 - (elapsedTime / 1000); // 남은 시간 계산
      if (countdownTime >= 1 && countdownTime <= 9) {
        displayNumber(lightNumber, countdownTime); // 디스플레이에 남은 시간을 표시
      }
      break;
  }
}

#endif
