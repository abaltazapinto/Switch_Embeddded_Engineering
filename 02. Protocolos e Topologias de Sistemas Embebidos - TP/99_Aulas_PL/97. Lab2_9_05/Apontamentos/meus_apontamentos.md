	DA3	
ip route -n 
	inicio 
		- destination 10.010.0 
		- gateway 0.0.0.0
		- Genmask 255.255.255.0
		- Flags U, metric and REF 0
		- Use 0
		- Iface eth0
		-
	stun
		- route add -net 0.0.0.0/0 gw 203.0.113.254

	ra
		- route add -net 0.0.0.0/0 gw 203.0.113.254
	rb
		- root@rb:/# route add -net 0.0.0.0/0 gw 203.0.113.254
	da1, da2, da3
root@da1:/# route add -net 0.0.0.0/0 gw 10.0.10.254
root@da2:/# route add -net 0.0.0.0/0 gw 10.0.10.254
root@da3:/# route add -net 0.0.0.0/0 gw 10.0.10.254
		root@da2:/# route add -net 0.0.0.0/0 gw 10.0.10.254
		root@da3:/# route add -net 0.0.0.0/0 gw 10.0.10.254

	db1, db2, db3
		root@db1:/# route add -net 0.0.0.0/0 gw 10.0.11.254
		root@db2:/# route add -net 0.0.0.0/0 gw 10.0.11.254
		root@db3:/# route add -net 0.0.0.0/0 gw 10.0.11.254
