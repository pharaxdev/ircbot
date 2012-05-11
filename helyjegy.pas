program helyjegy;
uses crt;
type jegy=record
        ules:integer;
        felszallas:integer;
        leszallas:integer;
end;
var     n:integer;
        vonal_hossz:integer;
        km10:integer;
        jegyek,c_jegyek:array[1..500]of jegy;
        ulesek:array[1..48] of integer;
procedure elso_feladat;
var     f:text;
        i:integer;
begin
assign(f,'eladott.txt');
reset(f);
readln(f,n,vonal_hossz,km10);
for i:=1 to n do
        readln(f,jegyek[i].ules,jegyek[i].felszallas,jegyek[i].leszallas);
close(f);
end;
procedure masodik_feladat;
begin
        writeln('2. feladat');
        writeln('Legutols¢ v†s†rl¢ ÅlÇssz†ma: ',jegyek[n].ules,'. Beutazott t†vols†g: ',jegyek[n].leszallas-jegyek[n].felszallas,'km.');
end;
procedure harmadik_feladat;
var     i:integer;
begin
        writeln('3. feladat');
        for i:=1 to n do
                if (jegyek[i].felszallas=0) and (jegyek[i].leszallas=vonal_hossz) then
                        write(i,' ');
        writeln;
end;
function jegyar(tav:integer):integer;
var ar,maradek:integer;
begin
        if (tav mod 10)=0 then
                ar:=round((tav/10)*km10)
        else
                ar:=round(((tav/10)+1)*km10);
        maradek:=ar mod 5;
        if maradek<3 then jegyar:=ar-maradek
        else    jegyar:=ar-maradek+5;
end;
procedure negyedik_feladat;
var     i:integer;
        ossz:longint;
begin
        ossz:=0;
        for i:=1 to n do
                ossz:=ossz+jegyar(jegyek[i].leszallas-jegyek[i].felszallas);
        writeln('4. feladat');
        writeln(ossz,' Ft bevÇtele van a t†rsas†gnak.');
end;
procedure otodik_feladat;
var     csere:jegy;
        count:integer;
        i,j:integer;
        leszallas:integer;
        felszallas:integer;
begin
        for i:=1 to n do c_jegyek[i]:=jegyek[i];
        for i:=n downto 1 do
        for j:=1 to i-1 do
                if c_jegyek[j].leszallas < c_jegyek[j+1].leszallas then
                        begin
                        csere:=c_jegyek[j+1];
                        c_jegyek[j+1]:=c_jegyek[j];
                        c_jegyek[j]:=csere;
                        end;
        leszallas:=c_jegyek[1].leszallas;
        i:=0;
        repeat
        i:=i+1;
        until (c_jegyek[i].leszallas <> leszallas);
        writeln(leszallas);
        for i:=1 to n do c_jegyek[i]:=jegyek[i];
        for i:=n downto 1 do
        for j:=1 to i-1 do
                if c_jegyek[j].felszallas < c_jegyek[j+1].felszallas then
                        begin
                        csere:=c_jegyek[j+1];
                        c_jegyek[j+1]:=c_jegyek[j];
                        c_jegyek[j]:=csere;
                        end;
        felszallas:=c_jegyek[1].felszallas;
        count:=0;
        if felszallas <= leszallas then
        begin
                for i:=1 to n do if (jegyek[i].felszallas=leszallas) or (jegyek[i].leszallas=leszallas) then
                count:=count+1;
        end
        else
        begin
                for i:=1 to n do if (jegyek[i].felszallas=felszallas) or (jegyek[i].leszallas=felszallas) then
                count:=count+1;
        end;
        writeln('5. feladat');
        writeln(count,' felsz†ll¢ Çs lesz†ll¢ utas volt');

end;
procedure hatodik_feladat;
var     hz:set of byte;
        i:integer;
        count:integer;
begin
        writeln('6. feladat');
        hz:=[];
        for i:=1 to n do
        begin
                hz:=hz+[jegyek[i].felszallas];
                hz:=hz+[jegyek[i].leszallas];
        end;
        count:=0;
        for i:=1 to vonal_hossz-1 do
                if i in hz then count:=count+1;
        writeln(count,' meg†ll¢hely volt.');
end;
procedure hetedik_feladat;
var     i,j:integer;
        f:text;
        pont:integer;
        hz:set of byte;
begin
        hz:=[];
        for i:=1 to n do
        begin
                hz:=hz+[jegyek[i].felszallas];
                hz:=hz+[jegyek[i].leszallas];
        end;
        writeln('KÇrem adjon meg egy t†vols†got');
        readln(pont);
        for i:=1 to 48 do ulesek[i]:=0;
        if pont in hz then
        begin
                for i:=1 to 48 do
                begin
                        for j:=1 to n do
                                if jegyek[j].ules=i then
                                begin
                                        if ((jegyek[j].felszallas < pont) and (jegyek[j].leszallas>pont))
                                                or (jegyek[j].felszallas=pont)
                                        then    ulesek[i]:=j;
                                end;
                end;
        end
        else
        begin
                for i:=1 to 48 do
                begin
                        for j:=1 to n do
                                if jegyek[j].ules=i then
                                begin
                                        if (jegyek[j].felszallas < pont) and (jegyek[j].leszallas > pont)
                                        then    ulesek[i]:=j;
                                end;
                end;
        end;
        assign(f,'kihol.txt');
        rewrite(f);
        for i:=1 to 48 do
                if ulesek[i]>0 then
                        writeln(f,i,'. ules: ',ulesek[i],'. utas')
                else
                        writeln(f,i,'. ules: ures');
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