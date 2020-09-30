cat /etc/passwd | awk -F ':' '{print $1" "$3" "$4}' > passwd_info.txt
