plot(datas/max(datas))
hold on
plot(datas2/max(datas2),'r')
hold on
plot(datas4/max(datas4),'b')
axis([100 24929 0 1.1])

datass=datas(100:end);
datass2=datas2(100:end)
datass3=datas3(100:end)

datass4=datas4(100:end)

plot(datass/max(datass))
hold on
plot(datass2/max(datass2),'r')
hold on
plot(datass3/max(datass3),'r')
hold on
plot(datass4/max(-datass4),'b')
axis([100 24929 0 1.1])