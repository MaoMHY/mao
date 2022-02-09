毛晗宇
发送邮箱：1796085874@qq.com 
仓库链接：https://github.com/quanbudongdetiangou/mao.git
任务：在一个运动视频中，做人脸检测，并对人脸添加滤镜。
任务进展：初步完成了人脸跟踪部分任务。两个项目对应两个实现方式。
QtConsoleApplication1项目是个qt项目，这种实现方式并没有用到目标跟踪算法，只是对每一帧进行人脸检测，速度慢但精度高。
ConsoleApplication5是对QtConsoleApplication1的改进，用人脸检测算法检测出人脸后形成初始跟踪框，之后调用跟踪器基于这个跟踪框进行跟踪。