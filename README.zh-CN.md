# 面向颈脖理疗的智能软体机器人

**基于 STM32 的多腔气囊、气泵与电磁阀控制系统**

[English](README.md) · [在线演示](https://wanju-boop.github.io/Embedded-Pneumatic-Pump-and-Valve-Control-System-/) · [固件入口](9-4%20串口收发文本数据包/User/main.c)

这是我在深圳大学完成的 **2024 年本科毕业设计**，围绕多腔软体气囊，集成 STM32 控制、充气与抽气气泵、电磁阀、气压采集，以及本地和手机端交互。

`C` `STM32F103C8T6` `PWM` `ADC` `UART` `ESP8266` `MQTT` `OLED`

<table>
  <tr>
    <td align="center"><a href="https://wanju-boop.github.io/Embedded-Pneumatic-Pump-and-Valve-Control-System-/#pneumatic-demo"><img src="docs/assets/pneumatic-preview.gif" width="270" alt="毕业设计气动软体机器人原始实机演示"></a></td>
    <td align="center"><a href="https://wanju-boop.github.io/Embedded-Pneumatic-Pump-and-Valve-Control-System-/#app-control-demo"><img src="docs/assets/app-control.jpg" width="270" alt="毕业设计手机端控制界面"></a></td>
  </tr>
  <tr>
    <td align="center"><b>气动软体机器人实机</b><br>原始演示视频的完整动图预览</td>
    <td align="center"><b>手机端控制界面</b><br>点击图片查看原始视频</td>
  </tr>
</table>

## 项目功能

- **气动执行：**通过充气泵、抽气泵和电磁阀，控制三层软体气囊的充放气与气路选择。
- **本地交互：**按键选择模式与运行状态，OLED 显示控制器状态。
- **嵌入式控制：**GPIO 与定时器 PWM 控制外部驱动模块，定时中断支持周期运行，ADC 采集气压传感器信号。
- **远程交互：**毕业设计通过 ESP8266 的串口 AT 指令链路连接阿里云，配合手机端界面进行控制。

项目面向颈部支撑与按摩应用开展原型研究。这里展示的是工程功能与实验记录，不作为临床疗效结论。

## 实机视频

以下 4 段视频直接提取自毕业答辩 PPT 第 12–13 页，保留原始画面与音轨。点击标题可在[演示页](https://wanju-boop.github.io/Embedded-Pneumatic-Pump-and-Valve-Control-System-/)直接播放，也可下载原始 MP4。

| 视频 | 时长 | 展示内容 |
|---|---:|---|
| [气动软体机器人演示](https://wanju-boop.github.io/Embedded-Pneumatic-Pump-and-Valve-Control-System-/#pneumatic-demo) | 24 秒 | 软体气囊、管路、控制板与实机运行 |
| [系统实物演示](https://wanju-boop.github.io/Embedded-Pneumatic-Pump-and-Valve-Control-System-/#system-demo) | 25 秒 | 气泵、接线与 OLED 状态 |
| [手机端控制演示](https://wanju-boop.github.io/Embedded-Pneumatic-Pump-and-Valve-Control-System-/#app-control-demo) | 11 秒 | 控制界面与连接的气泵 |
| [台架联调演示](https://wanju-boop.github.io/Embedded-Pneumatic-Pump-and-Valve-Control-System-/#bench-demo) | 23 秒 | 气囊与控制系统的台架布置 |

## 系统设计

整体设计由手机端、阿里云、ESP8266 和 STM32 组成通信链路。STM32 负责按键、传感器采集、显示及泵阀输出。

![毕业设计总体框架](docs/assets/system-overview.png)

<details>
<summary>展开查看气路连接与无线通信框图</summary>

**气路连接**

![气囊与泵阀连接图](docs/assets/pneumatic-layout.png)

**无线通信**

![ESP8266、阿里云与手机端连接关系](docs/assets/cloud-architecture.png)

</details>

## 硬件组成

| 模块 | 用途 |
|---|---|
| STM32F103C8T6 最小系统板 | 使用 C 与 STM32 标准外设库运行控制程序 |
| 充气气泵、抽气真空气泵 | 实现软体气囊的充气与抽气 |
| 电磁阀 | 选择气路 |
| 电机驱动及电源转换模块 | 连接 MCU 控制信号与泵阀负载 |
| RSCM17100KP020 气压传感器 | 提供模拟气压信号 |
| ESP8266 | 通过串口 AT 指令连接无线网络与云平台 |
| OLED 与按键 | 状态显示与本地操作 |

<table>
  <tr>
    <td align="center"><img src="docs/assets/inflation-pump.jpeg" width="220" alt="充气气泵实物"></td>
    <td align="center"><img src="docs/assets/vacuum-pump.jpeg" width="220" alt="抽气真空气泵实物"></td>
    <td align="center"><img src="docs/assets/controller.jpg" width="170" alt="控制板、OLED与台架接线"></td>
  </tr>
  <tr>
    <td align="center">充气气泵</td>
    <td align="center">抽气真空气泵</td>
    <td align="center">控制板与 OLED</td>
  </tr>
</table>

## 主要工作

毕业设计涵盖嵌入式程序、硬件集成与台架调试，论文和答辩材料记录了以下工作：

- 配置 STM32 外设，以主循环和中断组织按键、显示、传感器与执行器功能。
- 集成气泵、电磁阀、驱动与供电模块，并在调试中调整抽气泵的供电方案。
- 联调手机端、云端消息流转与 ESP8266 链路，排查云端设备之间因消息格式不匹配导致的通信问题。
- 开展模式切换、充放气和远程控制测试，保留实物照片及答辩演示视频。

## 固件入口

原始 Keil 工程位于 [`9-4 串口收发文本数据包`](9-4%20串口收发文本数据包)，沿用原目录名，保留最终固件文件。

| 文件 | 主要内容 |
|---|---|
| [`User/main.c`](9-4%20串口收发文本数据包/User/main.c) | 初始化、模式与状态控制、命令处理 |
| [`Hardware/Motor.c`](9-4%20串口收发文本数据包/Hardware/Motor.c) | 泵阀驱动接口 |
| [`Hardware/PWM.c`](9-4%20串口收发文本数据包/Hardware/PWM.c) | 定时器 PWM 配置 |
| [`Hardware/Serial.c`](9-4%20串口收发文本数据包/Hardware/Serial.c) | USART 通信与文本报文接收 |
| [`Hardware/AD.c`](9-4%20串口收发文本数据包/Hardware/AD.c) | 模拟量采集 |
| [`Hardware/Key.c`](9-4%20串口收发文本数据包/Hardware/Key.c)、[`Hardware/OLED.c`](9-4%20串口收发文本数据包/Hardware/OLED.c) | 按键与显示 |
| [`System/Timer.c`](9-4%20串口收发文本数据包/System/Timer.c) | 定时器配置 |

使用 Keil µVision 打开 [`Project.uvprojx`](9-4%20串口收发文本数据包/Project.uvprojx) 即可查看工程。工程目标器件为 STM32F103C8，使用 STM32 标准外设库；实机运行需结合原有接线及外部驱动模块。

## 归档说明

本仓库保留项目最终固件，图片、框图与视频来自 2024 年毕业设计材料。答辩材料记录了联网控制和气压阈值实验，当前归档 `main.c` 中相关联网初始化与阈值判断语句处于注释状态。因此，演示材料用于呈现当时的项目成果，不表示所有功能均在当前源码配置中启用；气压实验也不表述为经过标定的闭环压力控制。

**作者：**罗万驹 · 深圳大学，2024<br>
**毕业设计：**面向颈脖理疗的智能软体机器人的设计与实现<br>
**个人网站：**[wanju-luo.pages.dev](https://wanju-luo.pages.dev)
