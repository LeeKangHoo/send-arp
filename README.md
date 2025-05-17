<h1> How to use?</h1>

**./sendArp \<interface> \<victim> \<gateway>**

ex) ./sendArp wlan0 172.0.0.2 172.0.0.1

pcap라이브러리를 사용합니다.<br>

$ sudo apt install libpcap-dev<br>
$ sudo yum install libpcap-dev<br>

public한 네트워크에서 **악의적으로 사용X**<br>
arp infect 실습용 코드입니다.
