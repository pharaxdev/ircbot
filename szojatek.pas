program szojatek;
uses crt;
var     szo:string;
        van_e:boolean;
        i,j:integer;
        f:text;
        lHosszabb:string;
        vek:array[1..1000] of string[5];
        n_vek:integer;
procedure masodik_feladat;
var seged:string[20];
begin
assign(f,'szoveg.txt');
reset(f);
readln(f,lHosszabb);
while not eof(f) do
begin
        readln(f,seged);
        if length(seged) >length(lHosszabb) then lHosszabb:=seged;
end;
close(f);
writeln('A leghosszabb sz¢: ',lHosszabb,', ‚s ',length(lHosszabb),' db karakter!');
end;
{****************************************************************************}
procedure harmadik_feladat;
var     mg,msh:byte;
        hany_szo:integer;
        k:integer;
        seged_szo:string;
begin
assign(f,'szoveg.txt');
reset(f);
hany_szo:=0;
i:=0;
while not eof(f) do
begin
        i:=i+1;
        readln(f,seged_szo);
        mg:=0;
        msh:=0;
        for k:=1 to length(seged_szo) do
                if seged_szo[k] in ['a','e','o','u','i'] then
                        mg:=mg+1
                else msh:=msh+1;
        if mg>msh then
        begin
                write(seged_szo,' ');
                hany_szo:=hany_szo+1;
        end;
end;
close(f);
writeln;
writeln(hany_szo,'/',i,' : ',hany_szo/i:2:2,'%');
end;
{****************************************************************************}
{****************************************************************************}
procedure negyedik_seged;
var     seged:string;
begin
assign(f,'szoveg.txt');
reset(f);
n_vek:=0;
while not eof(f) do
begin
        readln(f,seged);
        if length(seged)=5 then
        begin
                n_vek:=n_vek+1;
                vek[n_vek]:=seged;
        end;
end;
close(f);
end;
procedure negyedik_feladat;
var     fok:string;
        m,n:integer;
begin
writeln;
writeln;
writeln('K‚rem a l‚tra fok t (3 betû)');
readln(fok);
for i:=1 to n_vek do
begin
        if (vek[i][2]=fok[1])
        AND (vek[i][3]=fok[2])
        AND (vek[i][4]=fok[3]) then
        write(vek[i],' ');
end;
writeln;
end;
{****************************************************************************}
{****************************************************************************}
procedure otodik_feladat;
var     fok:string;
        count:integer;
begin
assign(f,'letra.txt');
rewrite(f);
for i:=1 to n_vek-1 do
begin
        fok:=vek[i];
        delete(fok,1,1);
        delete(fok,4,1);
        count:=0;
        for j:=i+1 to n_vek do
        begin
                if (vek[j][2]=vek[i][2])
                AND (vek[j][3]=vek[i][3])
                AND (vek[j][4]=vek[i][4])
                AND (vek[j]<>'99999')
                then
                begin
                        if count = 0 then begin writeln(f,vek[i]); count:=1; end;
                        writeln(f,vek[j]);
                        vek[j]:='99999';
                end;
        end;
        if count=1 then writeln(f,'');
end;
close(f);
end;
{****************************************************************************}
begin
clrscr;
writeln('1. feladat Adjon meg egy sz¢t!');
readln(szo);
van_e:=false;
for i:=1 to length(szo) do
        if szo[i] in ['a','e','i','o','u'] then van_e:=true;
if van_e then writeln('Van benne mag nhangz¢.')
else writeln('Nincs benne mag nhangz¢.');
masodik_feladat;
harmadik_feladat;
negyedik_seged;
negyedik_feladat;
otodik_feladat;
readln;
end.