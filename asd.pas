program asd;
uses crt;
var     szoveg:string;
        i,j:integer;
begin
szoveg:='hheelloo';
for i:=1 to length(szoveg) do
for j:=i+1 to length(szoveg) do
        if szoveg[j]=szoveg[i] then delete(szoveg,j,1);
writeln(szoveg);
end.