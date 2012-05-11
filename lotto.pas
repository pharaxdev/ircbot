program lotto;
uses crt;
var i,j:integer;
        f:text;
        hz:set of byte;
        csere:integer;
        count:longint;
        bool:boolean;
        n:integer;
        vek:array[1..52,1..5]of byte;
        primek:array[1..90] of byte;
begin
assign(f,'lottosz.dat');
reset(f);
for i:=1 to 51 do
begin
        for j:=1 to 4 do
                read(f,vek[i][j]);
        readln(f,vek[i][j+1]);
end;
close(f);
writeln('Kerem adja meg az 52. het lotto szamait!');
read(vek[52][1]);
read(vek[52][2]);
read(vek[52][3]);
read(vek[52][4]);
readln(vek[52][5]);
for i:=5 downto 1 do
for j:=1 to i-1 do
begin
        if vek[52][j]>vek[52][j+1] then
        begin
                csere:=vek[52][j+1];
                vek[52][j+1]:=vek[52][j];
                vek[52][j]:=csere;
        end;
end;
for j:=1 to 5 do write(vek[52][j],' ');
writeln;
writeln('Adjon meg egy sz mot 1-51 k”z”tt!');
readln(i);
for j:=1 to 5 do
write(vek[i][j],' ');
writeln;
hz:=[];
for i:=1 to 52 do
for j:=1 to 5 do
hz:=hz+[vek[i][j]];
bool:=false;
for i:=1 to 90 do
if not(i in hz) then bool:=true;
if bool then writeln('van');
count:=0;
for i:=1 to 52 do
for j:=1 to 5 do
        if vek[i][j] MOD 2 > 0 then count:=count+1;
writeln(count,'db p ratlan sz m volt!');
assign(f,'lotto52.ki');
rewrite(f);
for i:=1 to 52 do
begin
        for j:=1 to 4 do write(f,vek[i][j],' ');
        writeln(f,vek[i][j+1]);
end;
close(f);
count:=0;
for n:=1 to 90 do
begin
for i:=1 to 52 do
for j:=1 to 5 do if n = vek[i][j] then count:=count+1;
write(count,' ');
if (n mod 15) = 0 then writeln;
count:=0;
end;
primek[1]:=2;
for i:=3 to 90 do
begin
bool:=false;
for j:=2 to i-1 do
        if (i mod j)=0 then bool:=true;
if not bool then if not(i in hz) then write(i,' ');
end;
writeln;
end.