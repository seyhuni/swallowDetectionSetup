if ~isempty(instrfind)
   fclose(instrfind);
   delete(instrfind);
end
ports = seriallist
s = serial(ports(end), "BaudRate",9600,'DataBits',8);

fopen(s);
%fprintf(s,'*IDN?')
index = 0;
datas = zeros(20000,1);
while(index<20000)
    index=index+1;
    out = fscanf(s);
%     datas(index)=str2num(fscanf(s));
    disp(out)
end
fclose(s);
clear s
clear
% uzunluk=linspace(-500,500,length(datas));
% 
% plot(uzunluk,abs(fftshift(fft(datas))))
%  
% Wn=2/500;
% [B,A] = butter(1,Wn,'low')
% Y = filter(B,A,datas)
% 
% 
