#include<iostream>

void end_game(){
	int count_me=0,count_opp=0;
	for(int i=1;i<=8;i++)
     for(int j=1;j<=8;j++){
       if(board[i][j]==me)       count_me++;
       else if(board[i][j]==opp) count_opp++;
     }
    if(count_me>count_opp) cout<<"you win"<<endl;
    else if(count_me==count_opp) cout<<"equal"<<endl;
    else cout<<"you lose"<<endl;
    cout<<"me:"<<count_me<<" "<<"AI:"<<count_opp;
} 

void printboard(){//打印当前棋盘
	dijibu++;
	cout<<"step: "<<dijibu<<endl;
    cout<<"   1  2  3  4  5  6  7  8"<<endl<<endl;
    for(int i=1;i<=8;i++){
 	cout<<i<<" |";
    for(int j=1;j<=8;j++) {
    	if(board[i][j]==1) cout<<"B"<<" |";
        else if(board[i][j]==2) cout<<"W"<<" |";	
        else cout<<"  |";
    }
    cout<<endl<<"  —————————————"<<endl;
    cout<<endl;
  }
 cout<<"___________________________"<<endl<<endl;
}

bool check_empty_board(int count1,int count2){
    for(int i=1;i<=8;i++) for(int j=1;j<=8;j++) if(qipan[count1][count2].cboard[i][j]!=0) return false;
    return true;
}

bool dfs_checklegal(int r,int c,int count,char role){//看能不能下在当前位置，被checklegal调用
   if(r<=0 || r>=9 || c<=0 || c>=9) return false;
   r=r+dirrr,c=c+dircc;
   if(board[r][c]==0) return false;
   else if(role=='p' && board[r][c]==opp){
   	count++;
    dfs_checklegal(r,c,count,'p');
   }
   else if(role=='c' && board[r][c]==me){
    count++;
    dfs_checklegal(r,c,count,'c');
   }
   else if(count>=1) return true;
   else return false;
}

bool checklegal(int r, int c,char role){ //i-->r && j-->c  判断该位置是否合法 
       if( board[r][c]!=0 ) return false; 
   	   else{
            for(int i=0;i<8;i++){
   				dirrr=dir_r[i];
   				dircc=dir_c[i];
   				if(dfs_checklegal(r,c,0,role)) return true; //判断在x=dirrr、y=dircc方向是否合法 	
  			}
  	   return false;
	 } 
}

int have_or_not(char role){
	for(int i=1;i<=8;i++) for(int j=1;j<=8;j++) if(checklegal(i,j,role)) return 1;
    return 0;
} 

bool board_dfs(int r,int c,int js,int count1,int count2,char role){
 		if(r<=0 || r>=9 || c<=0 || c>=9) return false;
 		r=r+dirrr,c=c+dircc;
	    if(qipan[count1][count2].cboard[r][c]==0) return false;
 		else if( role=='p' && qipan[count1][count2].cboard[r][c]==opp){
   			 js++;
   			 board_dfs(r,c,js,count1,count2,role);
 			}
 		else if( role=='c' && qipan[count1][count2].cboard[r][c]==me){
 			 js++;
             board_dfs(r,c,js,count1,count2,role);
 			}
		else if(js>=1) return true;
 		else return false;
}


bool board_endchecklegal(int r, int c,int count1,int count2,char role){//判断玩家想下的位置是否合法 
 		if(qipan[count1][count2].cboard[r][c]!=0) return false;
 		else{
  			for(int i=0;i<8;i++){
   					dirrr=dir_r[i];
  					dircc=dir_c[i];
   					if(board_dfs(r,c,0,count1,count2,role)) return true;//判断在x=dirrr、y=dircc方向是否合法 
                  }
  			return false;
 		} 
}
