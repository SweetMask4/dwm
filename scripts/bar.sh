#!/bin/sh

# ^c$var^ = fg color
# ^b$var^ = bg color

interval=0

# load colors
if [ -f "$HOME/repos/dwm/scripts/bar_themes/catppuccin" ]; then
. ~/repos/dwm/scripts/bar_themes/catppuccin
else
    echo "theme file not found" && exit 1
fi

cpu() {
  cpu_val=$(grep -o "^[^ ]*" /proc/loadavg)
  printf "^c$black^ ^b$green^ CPU"
  printf "^c$white^ ^b$grey^ $cpu_val"
}

pkg_updates() {
  #updates=$(doas xbps-install -un | wc -l) # void
  updates=$(checkupdates 2>/dev/null | wc -l) # arch
  # updates=$(aptitude search '~U' | wc -l)  # apt (ubuntu,debian etc)

  if [ -z "$updates" ]; then
    printf "  ^c$green^    Fully Updated"
  else
    printf "  ^c$green^    $updates"" updates"
  fi
}

battery() {
  if [ -f  /sys/class/power_supply/BAT1/capacity ];then 
  BAT=BAT1
  else
  BAT=BAT0
  fi
  get_capacity="$(cat /sys/class/power_supply/$BAT/capacity)"
  get_status="$(cat /sys/class/power_supply/$BAT/status)"

  if [ "$get_status" == "Discharging" ];then
    if (($get_capacity>98))
        then
            icon=" "
        elif (($get_capacity>75))
        then
            icon=" "
        elif (($get_capacity>40))
        then
            icon=" "
        elif (($get_capacity>10))
        then
            icon=" "
        else
            icon=" "
        fi
  else
  icon=" "
  fi
  printf "^c$blue^ $icon $get_capacity"
}

brightness() {
  printf "^c$red^   "
  printf "^c$red^%.0f\n" $(cat /sys/class/backlight/*/brightness)
}

mem() {
  printf "^c$blue^^b$black^  "
  printf "^c$blue^ $(free -h | awk '/^Mem/ { print $3 }' | sed s/i//g)"
}

wlan() {
	case "$(cat /sys/class/net/wl*/operstate 2>/dev/null)" in
	up) printf "^c$black^ ^b$blue^ 󰤨 ^d^%s" " ^c$blue^Connected" ;;
	down) printf "^c$black^ ^b$blue^ 󰤭 ^d^%s" " ^c$blue^Disconnected" ;;
	esac
}

clock() {
	printf "^c$black^ ^b$darkblue^ 󱑆 "
    printf "^c$black^^b$blue^$(date '+%b %d %Y - (%H:%M)') "
}

while true; do

  [ $interval = 0 ] || [ $(($interval % 3600)) = 0 ] && updates=$(pkg_updates)
  interval=$((interval + 1))

  sleep 1 && xsetroot -name "$updates $(battery) $(brightness) $(cpu) $(mem) $(wlan) $(clock)"
done
