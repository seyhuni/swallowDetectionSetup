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
datas = zeros(200,1);
datas2 = zeros(200,1);
datas3 = zeros(200,1);
datas4 = zeros(200,1);
tic
while(index<200)
    index=index+1;
    out = fscanf(s);
    if(length(str2num(out))>0)
     b=str2num(out);
     datas(index)=b(1);
     datas2(index)=b(2);
     datas3(index)=b(3);
     datas4(index)=b(4);

    end
    disp(out)
end
toc
fclose(s);
clear s
% uzunluk=linspace(-500,500,length(datas));
% 
% plot(uzunluk,abs(fftshift(fft(datas))))
%  
% Wn=2/500;
% [B,A] = butter(1,Wn,'low')
% Y = filter(B,A,datas)
% 
% 
