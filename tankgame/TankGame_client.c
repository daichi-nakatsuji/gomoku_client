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
	
    char msg[1024];
	char buffer[1024];

	//サーバからデータを受信
	recv(s, buffer, 1024, 0);
	printf("→ %s\n\n", buffer);

	while(1){
        //名前の入力
		printf("送信メッセージを入力(qで終了)");
		scanf("%s", msg);
		if(msg[0] == 'q' || msg[0] == 'Q'){
			break;
		}
		
		//サーバにデータを送信
		send(s, msg, strlen(msg), 0);

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