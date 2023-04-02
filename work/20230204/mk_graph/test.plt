

set multiplot 
set style fill solid border lc rgb "#FF4B00"
set boxwidth 1
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.9
set bmargin screen 0.65
set ytics add ('' 0)
set xlabel ''
set ylabel 'Count'
set noxtics 
plot[-1:50][-10:] "stat.dat" u   ($0):3 with boxes lw 2 lc rgb "#F6AA00" t "総カウント"   


# ----------------------------------
#
#
set style fill solid border lc rgb "blue"
#set boxwidth 1
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.65
set bmargin screen 0.40
set ylabel 'Count'
set ytics add ('' 0)
set noxtics 
plot[-1:50] "stat.dat" u ($0):4 with boxes lw 2 lc rgb "#4DC4FE" t "ミスタイプ"

# ----------------------------------
#
#
set lmargin screen 0.1
set rmargin screen 0.9
set tmargin screen 0.40
set bmargin screen 0.15
set xtics nomirror
set ylabel 'Typing error rate'
set ytics add ('0' 0)
plot[-1:50][-0.01:0.3] "stat.dat" u ($0):5:xtic(1) pt 7 lc rgb "#03AF7A" t "失敗率"
replot[-1:50] "stat.dat" u ($0):5:xtic(1) pt 6 lc rgb "dark-green" notitle

pause -1