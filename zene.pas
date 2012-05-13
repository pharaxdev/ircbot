program zene;
uses crt;
type rek=record
        radio:byte;
        hossz:longint;
        az:string[50];
        eloado,cim:string;
end;
var     n:integer;
        vek:array[1..1000] of rek;
procedure elso_feladat;
var     i:integer;
        f:text;
        min,sec:byte;
begin
        assign(f,'musor.txt');
        reset(f);
        readln(f,n);
        for i:=1 to n do
        begin
                readln(f,vek[i].radio,min,sec,vek[i].az);
                vek[i].hossz:=(min*60)+sec;
                delete(vek[i].az,1,1);
                vek[i].eloado:=copy(vek[i].az,1,pos(':',vek[i].az)-1);
                vek[i].cim:=copy(vek[i].az,pos(':',vek[i].az)+1,length(vek[i].az)-length(vek[i].eloado)-1);
        end;
end;
procedure masodik_feladat;
var     i:integer;
        n1,n2,n3:integer;
begin
        n1:=0;
        n2:=0;
        n3:=0;
        for i:=1 to n do
                case vek[i].radio of
                1: inc(n1);
                2: inc(n2);
                3: inc(n3);
                end;
        writeln('2. feladat');
        writeln('Az 1. ad¢n ',n1,' sz mot lehetett meghallgatni');
        writeln('A 2. ad¢n ',n2,' sz mot lehetett meghallgatni');
        writeln('A 3. ad¢n ',n3,' sz mot lehetett meghallgatni');
end;
procedure harmadik_feladat;
var     i:longint;
        ado:byte;
        ido:longint;
        lko,lke:integer;
begin
        ado:=1;
        lko:=0; lke:=0;
        for i:=1 to n do
        begin
                if (vek[i].radio=ado) and (vek[i].eloado='Eric Clapton') then
                begin
                        if lko=0 then lko:=i;
                end;
        end;
        for i:=n downto 1 do
        begin
                if (vek[i].radio=ado) and (vek[i].eloado='Eric Clapton') then
                        if lke=0 then lke:=i;
        end;
        ido:=vek[lko].hossz;
        for i:=lko to lke do
        begin
                if vek[i].radio=ado then
                        ido:=ido+vek[i].hossz;
        end;
        writeln('3. feladat');
        writeln(ido div 3600,':',(ido div 60) mod 60,':',ido mod 60);
end;
procedure negyedik_feladat;
var     i:integer;
        ado:byte;
        utolso:array[1..3] of string;
begin
        writeln('4. feladat');
        for i:=1 to 3 do utolso[i]:='';
        i:=1;
        while vek[i].az <> 'Omega:Legenda' do
        begin
                utolso[vek[i].radio]:=vek[i].az;
                inc(i);
        end;
        writeln(vek[i].radio,'. ad¢n ment az ',vek[i].az);
        ado:=vek[i].radio;
        for i:=1 to 3 do
                if i<> ado then writeln('A ',i,'. ad¢n jelenleg a: ',utolso[i],' volt hallhat¢!');
end;
procedure otodik_feladat;
var     i:integer;
        f:text;
        szoveg:string;
        temp:string;
        j:integer;
begin
        assign(f,'keres.txt');
        rewrite(f);
        writeln('5. feladat');
        write('K‚rem ¡rja be a felismert karaktereket: ');
        readln(szoveg);
        writeln(f,szoveg);
        for i:=1 to n do
        begin
                temp:=szoveg;
                for j:=1 to length(vek[i].az) do
                begin
                        if upcase(vek[i].az[j]) = upcase(temp[1]) then
                                delete(temp,1,1);
                end;
                if temp='' then writeln(f,vek[i].az);
        end;
        close(f);
end;
procedure hatodik_feladat;
var     i,k:integer;
        ido:longint;
        ado:byte;
        akt:longint;
        elso:array[1..1000] of rek;
begin
        k:=0;
        ado:=1;
        ido:=0;
        writeln('6. feladat');
        for i:=1 to n do
        begin
        if vek[i].radio=ado then begin
                if (ido mod 3600)=0 then
                begin
                        ido:=ido+180;
                        ido:=ido+vek[i].hossz;
                        ido:=ido+60;
                end
                else
                begin
                        akt:=ido+vek[i].hossz;
                        akt:=akt+60;
                        if ((ido mod 3600)>1800) and ((akt mod 3600)<=1800) then
                        begin
                                ido:=ido+(3600-(ido mod 3600));
                                ido:=ido+180;
                                ido:=ido+60;
                                ido:=ido+vek[i].hossz;
                        end
                        else ido:=(vek[i].hossz+60+ido);
                end;

        end;
        end;
        writeln(ido div 3600,':',(ido div 60) mod 60,':',ido mod 60);

end;
procedure f_hatodik;
var     i:integer;
        hossz,ido:integer;
begin
end;
begin
clrscr;
elso_feladat;
masodik_feladat;
harmadik_feladat;
negyedik_feladat;
otodik_feladat;
hatodik_feladat;
readln;
end.
