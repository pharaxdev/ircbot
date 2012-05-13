program foci;
uses crt;
type rek=record
        fordulo:byte;
        hazai_gol:byte;
        vendeg_gol:byte;
        hazai_fel_gol:byte;
        vendeg_fel_gol:byte;
        hazai:string[20];
        vendeg:string[20];
end;
var     n:integer;
        vek:array[1..400] of rek;
        csapat:string[20];
procedure elso_feladat;
var     i:integer;
        f:text;
begin
        assign(f,'meccs.txt');
        reset(f);
        readln(f,n);
        for i:=1 to n do
        begin
                readln(f,vek[i].fordulo,vek[i].hazai_gol,vek[i].vendeg_gol,vek[i].hazai_fel_gol,vek[i].vendeg_fel_gol,vek[i].hazai,vek[i].vendeg);
                delete(vek[i].hazai,1,1);
                vek[i].vendeg:=copy(vek[i].hazai,pos(' ',vek[i].hazai)+1,length(vek[i].hazai)-pos(' ',vek[i].hazai));
                delete(vek[i].hazai,pos(' ',vek[i].hazai),length(vek[i].vendeg)+1);
        end;
        close(f);
end;
procedure masodik_feladat;
var     i:integer;
        k:integer;
begin
        writeln('2. feladat');
        writeln('K‚rem ¡rjon be egy fordul¢sz mot');
        readln(k);
        if k>n then writeln('Hib s fordul¢sz m')
        else
        begin
                for i:=1 to n do
                        if vek[i].fordulo=k then
                        begin
                                write(vek[i].hazai,'-',vek[i].vendeg,': ');
                                writeln(vek[i].hazai_gol,'-',vek[i].vendeg_gol,' (',vek[i].hazai_fel_gol,'-',vek[i].vendeg_fel_gol,')');

                        end;
        end;
end;
procedure harmadik_feladat;
var     i:integer;
        hazai,vendeg:integer;
begin
        writeln('3. feladat');
        hazai:=0;
        vendeg:=0;
        for i:=1 to n do
        begin
                if ((vek[i].hazai_fel_gol>vek[i].vendeg_fel_gol) and (vek[i].hazai_gol<vek[i].vendeg_gol)) OR
                   ((vek[i].hazai_fel_gol<vek[i].vendeg_fel_gol) and (vek[i].hazai_gol>vek[i].vendeg_gol))
                   then
                   begin
                        write(vek[i].fordulo,'. fordul¢, Gy‹ztese:');
                        if vek[i].hazai_gol> vek[i].vendeg_gol then writeln(vek[i].hazai)
                        else writeln(vek[i].vendeg);
                   end;
        end;
end;
procedure negyedik_feladat;
begin
        writeln('K‚rem adjon meg egy csapatnevet!');
        readln(csapat);
end;
procedure otodik_feladat;
var     i,j:integer;
        lott,kapott:integer;
        vek2:array[1..400] of rek;
begin
        for i:=1 to n do
                vek2[i]:=vek[i];
        lott:=0;
        kapott:=0;
        for i:=1 to n do
        begin
                if vek2[i].hazai=csapat then
                begin
                        lott:=lott+vek2[i].hazai_gol;
                        kapott:=kapott+vek2[i].vendeg_gol;
                        for j:=1 to n do
                        begin
                                if vek2[j].hazai=vek2[i].vendeg then
                                begin
                                        vek2[j].hazai_gol:=0;
                                        vek2[j].vendeg_gol:=0;
                                end;
                        end;
                end
                else if vek2[i].vendeg=csapat then
                begin
                        lott:=lott+vek2[i].vendeg_gol;
                        kapott:=kapott+vek2[i].hazai_gol;
                        for j:=1 to n do
                        begin
                                if vek2[j].vendeg=vek2[i].hazai then
                                begin
                                        vek2[j].hazai_gol:=0;
                                        vek2[j].vendeg_gol:=0;
                                end;
                        end;
                end;
        end;
        writeln('l‹tt: ',lott,' kapott: ',kapott);
end;
procedure hatodik_feladat;
var     i,j:integer;
        csere:rek;
        ford:integer;
        vek2:array[1..400] of rek;
begin
        for i:=1 to n do
                vek2[i]:=vek[i];
        for i:=n downto 1 do
        for j:=1 to i-1 do
                if vek2[j].fordulo > vek2[j+1].fordulo then
                begin
                        csere:=vek2[j+1];
                        vek2[j+1]:=vek2[j];
                        vek2[j]:=csere;
                end;
        ford:=0;
        for i:=1 to n do
        begin
                if vek2[i].hazai=csapat then
                begin
                        if (ford=0) and (vek2[i].vendeg_gol>vek2[i].hazai_gol) then ford:=vek2[i].fordulo;
                end;
        end;
        if ford=0 then writeln('A csapat otthon veretlen maradt.')
        else writeln('A csapat a ',ford,'. fordul¢ban kapott ki el‹sz”r otthon.');
end;
procedure hetedik_feladat;
var     f:text;
        i,j:integer;
        count:integer;
begin
        assign(f,'stat.txt');
        rewrite(f);
        count:=0;
        for i:=1 to n do
        begin
                count:=1;
                if vek[i].hazai_gol < 99 then
                begin
                        write(f,vek[i].hazai_gol,'-',vek[i].vendeg_gol,': ');
                        for j:=i+1 to n do
                        begin
                                if ((vek[j].hazai_gol=vek[i].hazai_gol) and (vek[j].vendeg_gol=vek[i].vendeg_gol)) OR
                                        ((vek[j].hazai_gol=vek[i].vendeg_gol) and (vek[j].vendeg_gol=vek[i].hazai_gol))
                                        then
                                        begin
                                                inc(count);
                                                vek[j].hazai_gol:=99;
                                                vek[j].vendeg_gol:=99;
                                        end;
                        end;
                        writeln(f,count,' darab');
                end;
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