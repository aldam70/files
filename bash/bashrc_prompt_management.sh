################################################################################
# Set the bash prompt, depend of
#   - I am in a normal folder
#   - I am in a ClearCase view
#   - I am in a GIT repo
#   - And depend on if you are root or not
#
#
# Add the following lines to your .bashrc or .my_bashrc
# if you like to use this. And remove the '#' in front of the line
#
# ----- schnipp -----
# # ---------------------------------------
# # -- set PROMPT for bash
# # ---------------------------------------
# if [ -f /etc/bashrc_prompt_management.sh ]
# then
#   . /etc/bashrc_prompt_management.sh
# fi
# ----- schnapp -----
#
# Klaus Arndt, 03.02.2015
#
################################################################################

function select_prompt {
   local C_RED='\e[0;31m'
   local C_GREEN='\e[0;32m'
   local C_BLUE='\e[0;34m'
   local C_MAGENTA='\e[0;35m'
   local C_BACK_YELLOW='\e[0;43m'
   local C_CLEAR="\e[0m"
   GIT_BRANCH=$(git rev-parse --abbrev-ref HEAD 2>/dev/null)
   GIT_REPO=$(git rev-parse --show-toplevel 2>/dev/null)

   if   [[ -n "${CLEARCASE_ROOT}" && -z "${GIT_BRANCH}" ]] ; then
     # Set prompt for ClearCase-View
     # Turn the prompt symbol red if the user is root
     if [ $(id -u) -eq 0 ];
     then
       # you are root, make the prompt different
       PS1="\[${C_BACK_YELLOW}\]$( hostname )\[${C_CLEAR}\]:\[${C_BACK_YELLOW}\]\${PWD}\[${C_CLEAR}\][\[${C_GREEN}$( basename ${CLEARCASE_ROOT} )\[${C_CLEAR}\]]# "
     else
       PS1="\[${C_RED}\]$( hostname )\[${C_CLEAR}\]:\[${C_BLUE}\]\${PWD}\[${C_CLEAR}\][\[${C_GREEN}$( basename ${CLEARCASE_ROOT} )\[${C_CLEAR}\]]$ "
     fi
   elif [[ -n "${GIT_BRANCH}" && -z "${CLEARCASE_ROOT}" ]] ; then
     # Turn the prompt symbol different if the user is root
     if [ $(id -u) -eq 0 ];
     then 
       # you are root, make the prompt different
       PS1="\[${C_BACK_YELLOW}\]$( hostname )\[${C_CLEAR}\]:\[${C_BACK_YELLOW}\]\${PWD}\[${C_CLEAR}\][\[${C_MAGENTA}\]${GIT_BRANCH}\[${C_CLEAR}\]]# "
     else
       # Set prompt for GIT repo
       PS1="\[${C_RED}\]$( hostname )\[${C_CLEAR}\]:\[${C_BLUE}\]\${PWD}\[${C_CLEAR}\][\[${C_MAGENTA}\]${GIT_BRANCH}\[${C_CLEAR}\]]$ "
     fi
   elif [[ -n "${CLEARCASE_ROOT}" && -n "${GIT_BRANCH}" ]] ; then
     # Turn the prompt symbol different if the user is root
     if [ $(id -u) -eq 0 ];
     then 
       # you are root, make the prompt different
       PS1="\[${C_BACK_YELLOW}\]$( hostname )\[${C_CLEAR}\]:\[${C_BACK_YELLOW}\]\${PWD}\[${C_CLEAR}\][\[${C_GREEN}\]$( basename ${CLEARCASE_ROOT} )\[${C_CLEAR}\]][\[${C_MAGENTA}\]${GIT_BRANCH}\[${C_CLEAR}\]]# "
     else
       # Set prompt for ClearCase and GIT repo
       PS1="\[${C_RED}\]$( hostname )\[${C_CLEAR}\]:\[${C_BLUE}\]\${PWD}\[${C_CLEAR}\][\[${C_GREEN}\]$( basename ${CLEARCASE_ROOT} )\[${C_CLEAR}\]][\[${C_MAGENTA}\]${GIT_BRANCH}\[${C_CLEAR}\]]$ "
     fi
   else
     # Turn the prompt symbol different if the user is root
     if [ $(id -u) -eq 0 ];
     then
       # you are root, make the prompt different
       PS1="\[${C_BACK_YELLOW}\]$( hostname )\[${C_CLEAR}\]:\[${C_BACK_YELLOW}\]\${PWD}\[${C_CLEAR}\]# "
     else
       # Set normal prompt
       PS1="\[${C_RED}\]$( hostname )\[${C_CLEAR}\]:\[${C_BLUE}\]\${PWD}\[${C_CLEAR}\]$ "
     fi
   fi
}

# Setting the PROMPT_COMMAND variable will trigger bash to execute
# the function immediately before the prompt is displayed.
PROMPT_COMMAND="select_prompt"

# Cleanup
unset C_RED C_GREEN C_BLUE C_MAGENTA C_BACK_YELLOW C_CLEAR GIT_BRANCH GIT_REPO
