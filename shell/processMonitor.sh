#!/bin/bash
#输出到status_monitor.txt文件中，信息追加，非覆盖
#获取进程名称，外部输入
process=$1
#获取对应进程的pid
pid=$(pidof $process)
#写入相关提示信息
echo $process $pid >>status_monitor.txt
echo "  PID     USER      PR   NI    VIRT    RES    SHR  S  %CPU %MEM     TIME+   COMMAND" >>status_monitor.txt
#周期性查询信息并追加到status_monitor.txt文件中
while true
do
top -bn1 -n 1 -p $pid | tail -1 >>status_monitor.txt
#top -n 1 -b |grep -E $process >>status_monitor.txt
#sleep后面的数字单位为秒，下面为30s查询一次
sleep 3
done