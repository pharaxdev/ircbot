program telek;
uses crt;
type adat=record
        hazszam:integer;
        szelesseg:integer;
        hosszusag:integer;
end;
var n:byte;
        vek,c_vek:array[1..100] of adat;

procedure elso_feladat;
var     i:integer;
        f:text;
begin
        assign(f,'telkek.txt');
        reset(f);
        readln(f,n);
        for i:=1 to n do
        begin
                readln(f,vek[i].hazszam,vek[i].szelesseg,vek[i].hosszusag);
        end;
        close(f);
end;
procedure masodik_feladat;
var     i:integer;
        ossz:integer;
begin
        writeln('2. feladat');
        ossz:=0;
        for i:=1 to n do ossz:=ossz+vek[i].szelesseg;
        writeln(ossz,' mÇtert kell gyalogolnia.');
end;
procedure harmadik_feladat;
var     i:integer;
        ossz:integer;
begin
        writeln('3. feladat');
        ossz:=0;
        for i:=1 to 32 do
                if (vek[i].hazszam mod 2)=0 then
                        if vek[i].szelesseg <= 20 then
                                ossz:=ossz+1;
        writeln(ossz,' db telekre vonatkozik az elã°r†s.');
end;
function terulet(a,b:integer):integer;
begin
        terulet:=a*b;
end;
procedure negyedik_feladat;
var     i:integer;
        lk,ln:integer;
        count:byte;
begin
        lk:=1;
        for i:=1 to n do
                if (vek[i].hazszam mod 2)<>0 then
                        if terulet(vek[lk].hosszusag,vek[lk].szelesseg)> terulet(vek[i].hosszusag,vek[i].szelesseg) then
                                lk:=i;
        ln:=1;
        for i:=1 to n do
                if (vek[i].hazszam mod 2)<>0 then
                        if terulet(vek[ln].hosszusag,vek[ln].szelesseg)< terulet(vek[i].hosszusag,vek[i].szelesseg) then
                                ln:=i;
        count:=0;
        for i:=vek[lk].hazszam+1 to vek[ln].hazszam-1 do if (i mod 2)<>0 then count:=count+1;
        writeln('4. feladat');
        writeln(count,' h†z helyezkedik el kîzîttÅk');
        writeln('Legkisebb terÅlet˚ (',terulet(vek[lk].hosszusag,vek[lk].szelesseg),'m2) telek h†zsz†ma: ',vek[lk].hazszam,'.');
        writeln('Legnagyobb terÅlet˚ (',terulet(vek[ln].hosszusag,vek[ln].szelesseg),'m2) telek h†zsz†ma: ',vek[ln].hazszam,'.');

end;
procedure otodik_feladat;
const   hetszaz=51;
        hetszaz_ezer=39;
        ezer=200;
var     i:integer;
        ossz,osszesen:real;

begin
        osszesen:=0;
        for i:=1 to n do if (vek[i].hazszam mod 2)<>0 then
        begin
                ossz:=0;
                case terulet(vek[i].hosszusag,vek[i].szelesseg) of
                1..700: ossz:=ossz+(terulet(vek[i].hosszusag,vek[i].szelesseg)*hetszaz);
                701..1000:
                        begin
                        ossz:=ossz+(700*hetszaz);
                        ossz:=ossz+((terulet(vek[i].hosszusag,vek[i].szelesseg)-700)*hetszaz_ezer)
                         end;
                else
                        begin
                        ossz:=ossz+(700*hetszaz);
                        ossz:=ossz+(300*hetszaz_ezer);
                        ossz:=ossz+ezer;
                        end;
                end;
                if (vek[i].szelesseg<=15) or (vek[i].hosszusag<=25) then
                        ossz:=ossz*0.8;
                osszesen:=osszesen+ossz;
        end;
        writeln('5. feladat');
        writeln(osszesen:15:2,' Fabatk†ra sz†m°that az înkorm†nyzat.');
end;
procedure hatodik_feladat;
var     i,j:integer;
        max_paros:integer;
        tavolsag:integer;
        csere:adat;
begin
        max_paros:=1;
        for i:=1 to n do
                if vek[i].hazszam = 2 then max_paros:=i;
        for i:=1 to n do
                if (vek[i].hazszam mod 2)=0 then
                begin
                        if vek[i].hazszam > vek[max_paros].hazszam then max_paros:=i;
                end;
        for i:=1 to n do
                c_vek[i]:=vek[i];
        for i:=1 to n do
                if (c_vek[i].hazszam mod 2)<>0 then c_vek[i].hazszam:=0;
        for i:=n downto 1 do
        for j:=1 to i-1 do
                if c_vek[j].hazszam< c_vek[j+1].hazszam then
                begin
                        csere:=c_vek[j+1];
                        c_vek[j+1]:=c_vek[j];
                        c_vek[j]:=csere;
                end;
        tavolsag:=0;
        for i:=1 to n do
                if c_vek[i].hazszam<>0 then tavolsag:=tavolsag+c_vek[i].szelesseg;
        writeln('6. feladat');
        tavolsag:=tavolsag-c_vek[1].szelesseg;
        writeln(c_vek[1].hazszam,': ',tavolsag,'m');
        tavolsag:=tavolsag-c_vek[2].szelesseg;
        writeln(c_vek[2].hazszam,': ',tavolsag,'m');
        tavolsag:=tavolsag-c_vek[3].szelesseg;
        writeln(c_vek[3].hazszam,': ',tavolsag,'m');
end;
procedure hetedik_feladat;
var     i:integer;
begin
        writeln('7. feladat');
        for i:=1 to 10 do writeln('IMPOSSSIIIIIIIBRUUUUUUUUUUUUUUUUUUUUUUUUU');
end;
begin
clrscr;
elso_feladat;
masodik_feladat;
writeln;
harmadik_feladat;
writeln;
negyedik_feladat;
writeln;
otodik_feladat;
writeln;
hatodik_feladat;
writeln;
hetedik_feladat;
readln;
end.