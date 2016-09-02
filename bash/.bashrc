# ---------------------------------------
# -- set language
# ---------------------------------------

#LANG="zh_CN.GB18030"
#LANGUAGE="zh_CN.GB18030"

# ---------------------------------------
# -- source global definitions
# ---------------------------------------

if [ -f /etc/bashrc ]; then
	. /etc/bashrc
fi

# ---------------------------------------
# -- set alias
# ---------------------------------------

#alias ..='cd ..'
alias h='history'
alias j='jobs -l'
alias rm='rm -i'
alias cdws='cd /workspaces/atslxws155/adahuang/'
alias cdmi='cd /workspaces/atslxws155/adahuang/ws-r8.0-dev-adahuang-mi8/vobs/zenith/workspace/'
alias cdtcct='cd /workspaces/atslxws155/adahuang/ws-tcct-r2-dev-adahuang/workspace/'
alias cdphw='cd /workspaces/atslxws155/adahuang/ws-phcontrol-r1-dev-adahuang/workspace/'

alias cp='cp -i'
alias mv='mv -i'
alias ls='ls -F --color=tty'
alias la='ls -A --color=tty'
alias lt='ls -lhtrF --color=tty'
alias ll='ls -lh --color=tty'

osinfo=$(cat /etc/redhat-release)
if [ "$osinfo" = "Red Hat Enterprise Linux Workstation release 7.0 (Maipo)" ];
then
alias vi='/usr/bin/gvim'
alias cdh='cd /workspaces/atslxws155/adahuang/ws-phcontrol-r1-dev-adahuang/workspace/development/drivers/Generic_93K_Driver/GenericHandler/'
alias cdp='cd /workspaces/atslxws155/adahuang/ws-phcontrol-r1-dev-adahuang/workspace/development/drivers/Generic_93K_Driver/GenericProber//'
else
alias vi='~/bin/gvim'
alias cdhandler='cd /opt/93000/src/tci/handler'
alias cdprober='cd /opt/93000/src/tci/prober'
fi

alias pych='/home/adahuang/Downloads/pycharm-community-2016.1.4/bin/pycharm.sh >/dev/null 2>&1 &'
alias grep='grep --color=auto'
alias cman='man -M ~/share/man/zh_CN/'
alias ckon='~/bin/ckonsole.sh'
alias dict='stardict &'
alias which='type -all'
alias tsclient='tsclient >/dev/null 2>&1 &'
alias rdesktop_windows='rdesktop -u ADV\\adam.huang -g 1280x1024 -a 16 -r clipboard:PRIMARYCLIPBOARD 10.150.51.65 >/dev/null 2>&1 &'
alias eclipse='/home/adahuang/tools/eclipse/eclipse &'
alias lcdisplay='x0vncserver PasswordFile=/home/adahuang/.vnc/passwd &'
alias vncviewer='vncviewer &'
#alias vncsever='vncserver -geometry 1280x1024'

alias ct='/opt/rational/clearcase/bin/cleartool'
alias ci='ct ci -nc'
alias co='ct co -nc'
alias clrmake='/opt/rational/clearcase/bin/clearmake -V'
alias envmgr='/bstd_tools/contrib/lbin/envmgr'
alias mergemgr='/bstd_tools/contrib/lbin/mergemgr'
alias baseline='/bstd_tools/contrib/lbin/baseline'
alias lsview="ct lsview | grep 'adahuang'"
alias setview="/usr/atria/bin/cleartool setview"
alias setenv="/vobs/zenith/workspace/CMF-tools/set_environment.ksh"
alias lsco='ct lsco -avobs -cview'
alias ctdiff='ct diff -g -pre'
alias review="/bstd_tools/contrib/util/reviewtool/reviewtool.rb"
alias ccqcheck="/opt/ate/devtools/bin/doLocalCoverityAnalysis.sh"
#alias pwv='ct pwv'
#alias ccqcheck="/bstd_tools/contrib/lbin/qualitycheck.sh"

alias dsm=`echo $WORKSPACE`"/../../../opt/hp93000/soc/prod_env/bin/HPSmarTest -o &"
alias dkst=`echo $WORKSPACE`"/../../../opt/hp93000/soc/prod_env/lbin/kill_smarTest"
alias tsm='/opt/hp93000/soc/prod_env/bin/HPSmarTest -o &'
alias tkst='/opt/hp93000/soc/prod_env/lbin/kill_smarTest'

alias dtcct=`echo $WORKSPACE`"/system/bin/tcct"
alias dktcct=`echo $WORKSPACE`"/system/bin/killTcct"
alias ttcct='/opt/hp93000/testcell/bin/tcct -o &'
alias tktcct='/opt/hp93000/testcell/bin/killTcct -o &'

alias sw='/opt/hp93000/soc_common/bin/switch_version'
#alias tcct='/opt/hp93000/tcct/bin/tcct'
#alias killtcct='/opt/hp93000/tcct/bin/killTcct'
alias DRLDump='/opt/hp93000/soc/.service/bin/DRLDump -system -print -line'
export HP83000_ROOT=/opt/hp93000/soc
export PATH=$PATH:/opt/ibm/RationalSDLC/clearcase/linux_x86/bin/

# ---------------------------------------
# -- identify terminal
# ---------------------------------------

if [[ -t 0 ]]	# only if stdin is connected to a terminal
then
  export TTY_TYPE=`/usr/bin/tset -q`
  # Linux     Linux text console
  # xterm     xtem, konsole
fi

# ---------------------------------------
# -- set colors
# ---------------------------------------

case "$TTY_TYPE" in
"xterm" | "xterm-color" | "vt100" | "xterm-256color")
NORMAL="[0m"
BLACK="[30m"     #COLOR "[0m"
WHITE="[37m"     #COLOR "[0m"
GREEN="[32m"       #COLOR "[0m"
RED="[31m"     #COLOR "[0m"
YELLOW="[33m"    #COLOR "[0m"
BLUE="[0m[34m"      #COLOR "[0m"
MAGENTA="[35m"  #COLOR "[0m"
LIGHTBLUE="[36m" #COLOR "[0m"
REVYELLOW="[43m" #COLOR "[0m"
    ;;
  *)
    NORMAL=""
    BLACK=""
    WHITE=""
    GREEN=""
    RED=""
    YELLOW=""
    BLUE=""
    MAGENTA=""
    LIGHTBLUE=""
    REVYELLOW=""
    ;;
esac

# ---------------------------------------
# -- set PROMPT
# ---------------------------------------

#set normal prompt
PS1="\[${RED}\]`hostname`: \[${BLUE}\]\${PWD}\\[${NORMAL}\]\n\[${YELLOW}\]\\u:\[${NORMAL}\]$ "

# Set Prompt for ClearCase-Views
if [[ -n "${CLEARCASE_ROOT}" ]]
then
  PS1="\[${RED}\]`hostname`: \[${GREEN}\]/view/`basename ${CLEARCASE_ROOT}`: \[${BLUE}\]\${PWD}\[${NORMAL}\]
$ "
fi

export PS1

# ---------------------------------------
# -- set function
# ---------------------------------------
function ssv
{
  typeset PS3="Please select: "
  typeset SEARCH_PATH
  if [[ "${1}" = "" ]]
  then
    SEARCH_PATH=${LOGNAME}
  else
    SEARCH_PATH="$(echo "$@" |/bin/sed -e "s/ /*/g")"
  fi
  echo "Searching for viewtags contain \"*${SEARCH_PATH}*\"..."
  select VIEW in $(/usr/atria/bin/cleartool lsview -s \*${SEARCH_PATH}\*) Quit
  do
    if [[ ( "${VIEW}" != Quit ) && ( "${VIEW}" != "" )]]
    then
      echo "Set View:${VIEW}"
      /usr/atria/bin/cleartool setview  "${VIEW}"
      echo "Leave view:${VIEW}"
      break
    else
      echo "NO VIEW SET"
      break
    fi
  done
}

function ffile() {
	#find . -type f -iname '*'$*'*' -ls;
	find . -type f -iname "*$**" -ls;
}

function fstr() {
	OPTIND=1
    local case=""
    local usage="fstr: find string in files.
Usage: fstr [-i] \"pattern\" [\"filename pattern\"] "
    while getopts :it opt
    do
        case "$opt" in
        i) case="-i " ;;
        *) echo "$usage"; return;;
        esac
    done
    shift $(( $OPTIND - 1 ))
    if [ "$#" -lt 1 ]; then
        echo "$usage"
        return;
    fi
    local SMSO=$(tput smso)
    local RMSO=$(tput rmso)
    find . -type f -name "${2:-*}" -print0 | xargs -0 grep -sn ${case} "$1" 2>&- | \
sed "s/$1/${SMSO}\0${RMSO}/gI" | more
}

#function fexe() {
	#find . -type f -iname '*'$1'*' -exec "${2:-file}" {} \; ; 
#}

function cdls() {
	cd $1;
	ls;
}
alias cd=cdls

function up() {
	local dir=""
	count=$1
	for((i=1; i<=count; i++))
	do
	dir=$dir/..
	done
	dir=$(echo $dir | sed 's/^\///')
	if [ -z "$dir" ];then
		dir=..
	fi
	cd $dir;
}

#function mkdircd() {
	#mkdir -p "$@";
	#cd "$@"
#}
#alias mkdir='mkdircd'

function psgrep() {
	if [ ! -z $1 ];then
	echo "grepping for processes matching $1..."
	ps aux | grep $1 | grep -v grep
	else
	echo "!! need name to grep for"
	fi
}

#notes for reference
#sed -i "N;N;s/\n\nOLDSTRING/NEWSTRING/g" `grep "OLDSTRING" -rl .`
#socle113.bbn.verigy.net:1 12345678
