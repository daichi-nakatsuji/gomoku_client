#include <stdio.h>
#include <winsock2.h> //-lws2_32
#include <time.h>

int main(void) {	

	//接続するサーバの情報の構造体を用意

	struct sockaddr_in dest;

	memset(&dest, 0, sizeof(dest));

	//サーバの情報を入力

	char destination[100];  //アドレス
	int port;		//ポート番号

	printf("adress=");
	scanf("%s", destination);               //127.0.0.1
	printf("port=");
	scanf("%d", &port);                     //11000
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
	char name[] = "name:GoPT\n";
    char move[9][20] = {"move:100\n", "move:200\n", "move:300\n", "move:400\n", "move:500\n", "move:600\n", "move:700\n", "move:800\n", "move:900\n"};
	char cannon[9][20] = {"cannon:100\n", "cannon:200\n", "cannon:300\n", "cannon:400\n", "cannon:500\n", "cannon:600\n", "cannon:700\n", "cannon:800\n", "cannon:900\n"};
	char search[11][20] = {"search:0\n", "search:100\n", "search:200\n", "search:300\n", "search:400\n", "search:500\n", "search:600\n", "search:700\n", "search:800\n", "search:900\n", "search:1000\n"};
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

	int Hight = 5;
	int MyHight = 0;
	int x, y;
	int cannon_num;
	char Search_Result[20];
	char null[1024] = "search_result:null\n";
	time_t t = time(NULL);
	srand(t);

	while(1){
		//自身の座標を確認
		send(s, state[1], strlen(state[1]), 0);
		//サーバからデータを受信
        memset(buffer, '\0', sizeof(buffer));
	    recv(s, buffer, sizeof(buffer), 0);
	    printf("→ %s", buffer);
		
		//フィールドの上部と下部どちらにいるか
		sscanf(buffer, "state_hight_result:%d\n", &Hight);
		Hight /= 100;
		if(Hight >= 5){
			MyHight = 0;
		}else{
			MyHight = 1;
		}

		//防御
		if(MyHight == 0){
			//自身の上部を確認
			send(s, search[0], strlen(search[0]), 0);
			//サーバからデータを受信
        	memset(buffer, '\0', sizeof(buffer));
	    	recv(s, buffer, sizeof(buffer), 0);
	    	printf("→ %s", buffer);

			//移動指示
			if(strcmp(buffer, null) == 0){
				send(s, move[Hight - 5], strlen(move[Hight - 5]), 0);
				//サーバからデータを受信
    			memset(buffer, '\0', sizeof(buffer));
	    		recv(s, buffer, sizeof(buffer), 0);
	    		printf("→ %s", buffer);
			}else{
				sscanf(buffer, "search_result:%d,%d,%s\n", &x, &y, Search_Result);
				if(y <= 700){
					send(s, move[y/100 + 2], strlen(move[y/100 + 2]), 0);
					//サーバからデータを受信
    				memset(buffer, '\0', sizeof(buffer));
	    			recv(s, buffer, sizeof(buffer), 0);
	    			printf("→ %s", buffer);
				}
			}
		}else if(MyHight == 1){
			//自身の下部を確認
			send(s, search[10], strlen(search[10]), 0);
			//サーバからデータを受信
        	memset(buffer, '\0', sizeof(buffer));
	    	recv(s, buffer, sizeof(buffer), 0);
	    	printf("→ %s", buffer);
			if(strcmp(buffer, null) == 0){
				send(s, move[Hight + 4], strlen(move[Hight + 4]), 0);
				//サーバからデータを受信
    			memset(buffer, '\0', sizeof(buffer));
	    		recv(s, buffer, sizeof(buffer), 0);
	    		printf("→ %s", buffer);
			}else{
				sscanf(buffer, "search_result:%d,%d,%s\n", &x, &y, Search_Result);
				if(y >= 200){
					send(s, move[y/100 - 2], strlen(move[y/100 - 2]), 0);
					//サーバからデータを受信
    				memset(buffer, '\0', sizeof(buffer));
	    			recv(s, buffer, sizeof(buffer), 0);
	    			printf("→ %s", buffer);
				}
			}
		}

		Sleep(1000*(rand()%3+1));
		

		//攻撃
		send(s, state[2], strlen(state[2]), 0);
		//サーバからデータを受信
    	memset(buffer, '\0', sizeof(buffer));
		recv(s, buffer, sizeof(buffer), 0);
    	printf("→ %s", buffer);
		sscanf(buffer, "state_cannon_result:%d", &cannon_num);
		//自身の高さから上下2か所にキャノンを打つ
		if(cannon_num >= 2 && Hight > 1 && Hight < 8){
			send(s, cannon[Hight+1], strlen(cannon[Hight+1]), 0);
			//サーバからデータを受信
    		memset(buffer, '\0', sizeof(buffer));
	    	recv(s, buffer, sizeof(buffer), 0);
	    	printf("→ %s", buffer);
			Sleep(1000);

			send(s, cannon[Hight], strlen(cannon[Hight]), 0);
			//サーバからデータを受信
    		memset(buffer, '\0', sizeof(buffer));
	    	recv(s, buffer, sizeof(buffer), 0);
	    	printf("→ %s", buffer);
			Sleep(1000);

			send(s, cannon[Hight-1], strlen(cannon[Hight-1]), 0);
			//サーバからデータを受信
    		memset(buffer, '\0', sizeof(buffer));
	    	recv(s, buffer, sizeof(buffer), 0);
	    	printf("→ %s", buffer);
		}else if(cannon_num >= 2 && Hight >= 8){
			send(s, cannon[Hight - 2], strlen(cannon[Hight -1]), 0);
			//サーバからデータを受信
    		memset(buffer, '\0', sizeof(buffer));
	    	recv(s, buffer, sizeof(buffer), 0);
	    	printf("→ %s", buffer);
			Sleep(1000);

			send(s, cannon[Hight-1], strlen(cannon[Hight-1]), 0);
			//サーバからデータを受信
    		memset(buffer, '\0', sizeof(buffer));
	    	recv(s, buffer, sizeof(buffer), 0);
	    	printf("→ %s", buffer);
		}else if(cannon_num >= 2 && Hight == 1){
			send(s, cannon[Hight+1], strlen(cannon[Hight+1]), 0);
			//サーバからデータを受信
    		memset(buffer, '\0', sizeof(buffer));
	    	recv(s, buffer, sizeof(buffer), 0);
	    	printf("→ %s", buffer);
			Sleep(1000);

			send(s, cannon[Hight+2], strlen(cannon[Hight+2]), 0);
			//サーバからデータを受信
    		memset(buffer, '\0', sizeof(buffer));
	    	recv(s, buffer, sizeof(buffer), 0);
	    	printf("→ %s", buffer);
		}
	}

	// Windows でのソケットの終了
	closesocket(s);
	WSACleanup();
	return 0;

}