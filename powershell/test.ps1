Get-Process
Get-Process | Where-Object {$_.PriorityClass -eq "Normal"} > out.txt
Get-Process | Where-Object {$_.Responding -eq "True"} | Out-File out.txt

Get-Service | Where-Object {$_.Status -eq "Stopped"} | Out-File out.txt

Get-PSDrive > .\out.txt

dir cert: > out.txt
