# V4L2_test
V4L2에서 카메라 신호를 받아와서 이를 openCV의 UI에 보여주는 기능.

### 빌드
```
g++ -o v4l2_test v4l2_test.cpp `pkg-config --cflags --libs opencv4` 
```

### 실행
```
./v4l2_test
```

# Camera Application
V4L2를 통해 받은 카메라 신호를 Qt5 GUI로 시각화.