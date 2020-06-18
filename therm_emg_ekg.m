clear
if ~isempty(instrfind)
   fclose(instrfind);
   delete(instrfind);
end
ports = seriallist
s = serial(ports(end), "BaudRate",115200,'DataBits',8,'Terminator','LF');

fopen(s);
%fprintf(s,'*IDN?')
index = 0;
datas = 0;
datas2 =0;
datas3 =0;

tic
 h = figure(1);
 while 1 
    index=index+1;
    out = fscanf(s);
    if(length(str2num(out))>0)
     b=str2num(out);
     datas(index)=b(1);
     datas2(index)=b(2);
     datas3(index)=b(3);
     
    end
    disp(out)
     drawnow
     isKeyPressed = ~isempty(get(h,'CurrentCharacter'));
     if isKeyPressed
         break
     end

end
toc
fclose(s);
clear s
figure
subplot(3,1,1)
plot(datas)
title('swallow')
subplot(3,1,2)
plot(datas2,'r')
title('nasal air flow')
subplot(3,1,3)
plot(datas3,'k')
title('ekg')
% subplot(4,1,4)
% plot(datas4,'k')
% title('consumed liquid mass')

% uzunluk=linspace(-71,71,length(datas3));
% 
% plot(uzunluk,abs(fftshift(fft(datas3-mean(datas3)))))
 
% Wn=2/500;
% [B,A] = butter(1,Wn,'low')
% Y = filter(B,A,datas)
% 
% 




