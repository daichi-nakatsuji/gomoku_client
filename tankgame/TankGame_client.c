#include <stdio.h>
#include <winsock2.h> //-lws2_32


int main(void) {	

	//接続するサーバの情報の構造体を用意

	struct sockaddr_in dest;

	memset(&dest, 0, sizeof(dest));

	//サーバの情報を入力

	char destination[100];  //アドレス
	int port;		//ポート番号

	printf("アドレスを入力してください");
	scanf("%s", destination);
	printf("ポート番号を入力してください");
	scanf("%d", &port);
	dest.sin_port = htons(port);
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = inet_addr(destination);

	//ソケット通信の準備・生成
	WSADATA data;
	WSAStartup(MAKEWORD(2, 0), &data);
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	//サーバへの接続
	if (connect(s, (struct sockaddr *) &dest, sizeof(dest))) {
		printf("%sに接続できませんでした\n", destination);
		return -1;

	}

	printf("%sに接続しました\n", destination);
	
    char buffer[1024];
	char name[] = "name:SAMPLE\n";
    char move[9][20] = {"move:100\n", "move:200\n", "move:300\n", "move:400\n", "move:500\n", "move:600\n", "move:700\n", "move:800\n", "move:900\n"};
	char cannon[9][20] = {"cannon:100\n", "cannon:200\n", "cannon:300\n", "cannon:400\n", "cannon:500\n", "cannon:600\n", "cannon:700\n", "cannon:800\n", "cannon:900\n"};
	char search[9][20] = {"search:100\n", "search:200\n", "search:300\n", "search:400\n", "search:500\n", "search:600\n", "search:700\n", "search:800\n", "search:900\n"};
	char state[3][20] = {"state:hp\n", "state:hight\n", "state:cannon\n"};
	
	//サーバにデータを送信：名前の送信
	send(s, name, strlen(name), 0);
	
	//サーバからデータを受信：nameの返信 を受け取る
	memset(buffer, '\0', sizeof(buffer));
	recv(s, buffer, sizeof(buffer), 0);
	printf("→ %s\n\n", buffer);

	//サーバからデータを受信：START を受け取る
	memset(buffer, '\0', sizeof(buffer));
	recv(s, buffer, sizeof(buffer), 0);
	printf("→ %s\n\n", buffer);

	while(1){
        char buffer2[1024];
		//サーバからデータを受信
        memset(buffer2, 0, sizeof(buffer2));
		recv(s, buffer2, 1024, 0);
		printf("→ %s\n\n", buffer2);
	}

	// Windows でのソケットの終了
	closesocket(s);
	WSACleanup();
	return 0;

}