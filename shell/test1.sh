echo "First variable:" $0
echo "pwd is:" 'pwd'
echo "pwd is:" "pwd"
echo "-------------"
echo "Variable1" `pwd` # 两个效果一致
echo "Variable1" $(pwd)
echo "-------------"
# test ‘’ and  “”
echo "Variable2:" '$(pwd)'
echo "Variable2:" "$(pwd)"
echo "-------------"
echo "Variable3:" "'$(pwd)'"
echo "Variable3:" '"$(pwd)"'

# SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" >/dev/null 2>&1 && pwd)"
# echo "test: " "${BASH_SOURCE[0]}"
# echo "test: " "$0"
# echo "Project dir: " ${SCRIPT_DIR}

# set path=pwd
# echo "test for: " ${$(pwd)}