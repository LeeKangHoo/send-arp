<h1> How to use?</h1>

**./sendArp \<interface> \<victim> \<gateway>**

ex) ./sendArp wlan0 172.0.0.2 172.0.0.1

pcap라이브러리를 사용합니다.<br>

$ sudo apt install libpcap-dev<br>
$ sudo yum install libpcap-dev<br>

public한 네트워크에서 **악의적으로 사용X**<br>
arp infect 실습용 코드입니다.

추후에 victim -> gateway, gateway -> victim 
두 개의 flow에서 통신이 가능하도록 기능을 추가하며 attacker가 가운데서 relay하도록 업데이트할 예정입니다.
