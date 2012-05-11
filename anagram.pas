program anagram;
uses crt;
var     i,j,k,l:integer;
        n:integer;
        f:text;
        vek,c_vek:array[1..300] of string[30];
        veks,vekcount:array[1..300] of integer;
procedure elso_feladat;
var szoveg:string;
        count:integer;
begin
        writeln('1. feladat Adjon meg egy szîveget!');
        readln(szoveg);
        for i:=1 to length(szoveg) do
        for j:=i+1 to length(szoveg) do
        begin
                if szoveg[j]=szoveg[i] then
                begin
                        {delete(szoveg,j-1,1); }
                        szoveg[j]:='$';
                end;
        end;
        count:=0;
        for i:=1 to length(szoveg) do
        if (szoveg[i]<>'$') and (szoveg[i]<>' ') then count:=count+1;
        writeln(count,' db kÅlînbîzã karakter van a szîvegben!');
        for i:=1 to length(szoveg) do if (szoveg[i]<>'$') and (szoveg[i]<>' ') then write(szoveg[i],', ');
        writeln;
end;
procedure masodik_feladat;
begin
n:=0;
assign(f,'szotar.txt');
reset(f);
while not eof(f) do
begin
n:=n+1;
readln(f,vek[n]);
c_vek[n]:=vek[n];
end;
close(f);
end;
procedure rendez(var temp:string);
var csere:char;
begin
  for i:=length(temp) downto 1 do
        for j:=1 to i-1 do
        begin
                if temp[j]>temp[j+1] then
                begin
                        csere:=temp[j+1];
                        temp[j+1]:=temp[j];
                        temp[j]:=csere;
                end;
        end;
end;
procedure harmadik_feladat;
var csere:char;
begin
assign(f,'abc.txt');
rewrite(f);
for k:=1 to n do
begin
        rendez(c_vek[k]);
        writeln(f,c_vek[k]);
end;
close(f);
end;
procedure negyedik_feladat;
var elso,masodik:string;
begin
writeln('KÇrem az elsã sz¢t!');
readln(elso);
writeln('KÇrem a m†sodik sz¢t!');
readln(masodik);
rendez(elso);
rendez(masodik);
if elso = masodik then writeln('Anagramma!') else writeln('Nem anagramma!');
end;
procedure otodik_feladat;
var seged:string;
        szo:string;
        count:integer;
begin
writeln('KÇrek egy sz¢t!');
readln(szo);
count:=0;
rendez(szo);
for i:=1 to n do
        if szo=c_vek[i] then begin writeln(vek[i]);  count:=1; end;
if count=0 then writeln('Nincs a sz¢t†rban anagramma');
end;
procedure hatodik_feladat;
var     max:integer;
        db:integer;
begin
        max:=1;
        for i:=1 to n do
                if length(c_vek[i])> length(c_vek[max]) then max:=i;
        db:=0;
        for i:=1 to n do
                if length(c_vek[i]) = length(c_vek[max]) then
                begin
                db:=db+1;
                veks[db]:=i;
                end;
        for i:=1 to db do
        begin
                for j:=1 to db do
                begin
                        if c_vek[veks[i]]=c_vek[veks[j]] then vekcount[i]:=vekcount[i]+1;
                         end;
        end;
        max:=1;
        for i:=1 to db do
        begin
                if vekcount[i]>vekcount[max] then max:=i;
        end;
        for i:=1 to db do
        if c_vek[veks[i]]=c_vek[veks[max]] then writeln(vek[veks[i]]);

end;
procedure hetedik_feladat;
var     csere,csere_2:string;
        volt_bent:boolean;
        hossz:integer;
begin
        for i:=n downto 1 do
        for j:=1 to i-1 do
        begin
                if length(vek[j])>length(vek[j+1]) then
                begin
                        csere:=vek[j+1]; csere_2:=c_vek[j+1];
                        vek[j+1]:=vek[j]; c_vek[j+1]:=c_vek[j];
                        vek[j]:=csere;   c_vek[j]:=csere_2;
                end;
        end;
        assign(f,'rendezve.txt');
        rewrite(f);
        for i:=1 to n do
        begin
                if c_vek[i]<>'$' then begin write(f,vek[i],' ');  hossz:=length(vek[i]); end;
                volt_bent:=false;
                for j:=i+1 to n do
                begin
                        if (c_vek[i]=c_vek[j]) and (c_vek[j]<>'$') then
                        begin
                        write(f,vek[j],' ');
                        c_vek[j]:='$';
                        volt_bent:=true;
                        end;
                end;
                if volt_bent then writeln(f,' ');
                if (c_vek[i+1]<>'$') and (length(c_vek[i+1])<>hossz) then writeln(f,' ');
        end;
        close(f);
end;
begin
clrscr;
elso_feladat;
masodik_feladat;
harmadik_feladat;
negyedik_feladat;
otodik_feladat;
hatodik_feladat;
hetedik_feladat;
readln;
end.