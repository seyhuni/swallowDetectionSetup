if ~isempty(instrfind)
   fclose(instrfind);
   delete(instrfind);
end
ports = seriallist
s = serial(ports(end), "BaudRate",9600,'DataBits',8);

fopen(s);

index = 0;
data=[];
while(index<10000)
    index=index+1;
    new_data = fscanf(s);
    data=[data;str2num(new_data)];
%      plot(data);drawnow 
end
fclose(s);
clear s
clear