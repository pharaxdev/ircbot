program rejtvenyfeladat;
uses crt;
type rejtveny=record
        nev:string;
        tabla:array[1..10,1..10] of byte;
end;
var vek:array[1..20] of rejtveny;
        f:text;
        torony:array[1..2]of byte;
        hajok:byte;
        megoldasok:integer;
        i,j,k,l:integer;
procedure beolvas;
var m,n:byte;
begin
        assign(f,'megoldas.txt');
        reset(f);
        readln(f,megoldasok);
        for i:=1 to megoldasok do
        begin
                readln(f,vek[i].nev);
                for m:=1 to 10 do
                begin
                for n:=1 to 9 do
                read(f,vek[i].tabla[m][n]);
                readln(f,vek[i].tabla[m][n+1]);
                end;
        end;
        close(f);
end;
procedure kiir;
begin
for k:=1 to megoldasok do
begin
for i:=1 to 10 do
begin
for j:=1 to 9 do
write(vek[k].tabla[i][j]:2,' ');
writeln(vek[k].tabla[i][j+1]:2);
end;
writeln; writeln; writeln;
end;
end;
procedure elso_f;
begin
writeln('Adja meg a torony adatait!');
read(torony[1]);
readln(torony[2]);
writeln('Adja meg a toronyb¢l l that¢ haj¢k sz m t!');
readln(hajok);
if hajok > 3 then writeln('Neh‚z torony.');
end;
begin
clrscr;
beolvas;
elso_f;
end.
