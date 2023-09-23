# ./bin/fast_detect
###
 # @Author: jiajunwang 18035173529@163.com
 # @Date: 2023-06-07 14:49:09
 # @LastEditors: Please set LastEditors
 # @LastEditTime: 2023-09-22 20:22:07
 # @FilePath: /testOpencv/run.sh
 # @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
### 
# ./bin/testOpencv
# ./bin/test
# ./bin/test_resize
# ./bin/test_orb -d ./data/1403636859301666560.png -f /home/larry/Documents/LearnSpace/LarryVisionSpace/opencv/script/EuRoC.yaml
# ./bin/useColorMap data/disparity.png
# ./bin/useMat

# ./bin/disparity_filtering ./data/ambush_5_left.jpg ./data/ambush_5_right.jpg
./bin/disparity_filtering ./data/left.png ./data/right.png \
--dst_path=./data/res/afterFilter.png \
--dst_raw_path=./data/res/disp.png 