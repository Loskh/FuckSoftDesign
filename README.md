# FuckSoftDesign
## Fuck the Software Design Week

## A档
------
###  一、分数统计（10）
要求：  

    （1）输入某班级学生的姓名、分数；
    （2）对（1）的分数进行降幂排列并输出；
    （3）具有输入输出界面。
### 二、打字程序（10）
要求：  

     （1）随即产生一字符串，每次产生的字符串内容、长度都不同；
     （2）根据（1）的结果，输入字符串，判断输入是否正确，输出正确率；
     （3）具有输入输出界面。
### 三、文本编辑器（10）
要求：  

    （1）编辑文本；
    （2）保存、打开指定位置的文本文件；
    （3）具有输入输出界面。
### 四、加密（10）
要求：  

    （1）输入任意一段明文M，以及密钥K;
    （2）根据以下公式将其转换为密文C。
     Ci  =  Mi  +  K  ,其中i = 0,1,……n-1 , K 为密钥；
    （3）具有输入输出界面。
### 五、进制转换器（10）
要求：  

    （1）可输入二进制、八进制、十进制、十六进制数；
    （2）将已输入的数转换成其余进制的数；
    （3）具有输入输出界面。
-----
## B档
### 一、学生成绩核算系统的设计与实现（25）
要求：  

    （1）按班级按课程从文件中读入相应的平时成绩、期中考试成绩和期末考试成绩。
    （2）三个成绩对总评成绩的百分比被定义为常数，各占总成绩的30%、30%和40%。
    （3）计算每位学生的总评成绩。
    （4）计算该班级本课程的总平均成绩。
    （5）计算处于优、良、中、及格、不及格的学生人数以及占总人数的百分比。其中100-90为优，89-80为良，79-70为中，69-60为及格，60分以下为不及格。
    （6）按要求输出成绩在优、良、中、及格、不及格各区间的学生学号、成绩。
程序设计参考思路：  

1.  建立文本文件 note.dat，第一行为学生的总人数，其后为每个学生的成绩，每个学生的信息占一行，格式为:
    <pre><code>学号(6位)  平时成绩  期中考试成绩  期末考试成绩
    </code></pre>
    例如：
    <pre><code>15
    994201     88    		75.5  			66         
    994202     91    		79.5  			76
    994203     85   		75   			77        
    994204     79    		82    			80.5
    994205     94    		83.5  			81.5       
    994206     80    		69    			68
    994207     82    		77    			71        
    994208     77    		57    			58
    994209     91    		88    			86        
    994210     96    		89    			90
    994211     70    		45.5   			50        
    994212     74    		65    			66
    994213     81    		71    			76        
    994214     83    		75    			77
    994215     85    		78    			79      
    </code></pre>

2.  从文件中读入相应的平时成绩、期中考试成绩和期末考试成绩时，数据的读入方式可用C语言中的文件读入方式进行，也可用C++中的流实现.  
3.  每次计算出的结果可在屏幕输出，并把每个学生的总评成绩输入到新文件out.dat文件中
格式为：  
    <pre><code>学生学号(6位)   总评成绩   成绩等级</code></pre>
    例如:<pre><code>984201         88         B</code></pre>
4.  数据结构（可用C++实现）  
    两个类：<pre><code>学生（student）和学生成绩（marks）</code></pre>  
    (1)学生类  
    数据成员：<pre><code>学号、姓名、专业等</code></pre>  
    数据类型  
    属性（私有、保护、公有）  
    方法：构造函数和析构函数  
        设置学号	<pre><code>void SetId( long );</code></pre>   
        读取学号	<pre><code>long GetId( ); </code></pre>  
        等等  
(2)学生成绩类 —— 从学生类派生  
数据成员：  
    平时成绩、期中考试成绩、期末考试成绩、总评成绩、成绩等级     
数据类型  
    属性（私有、保护、公有）  
方法：  
    读入成绩<pre><code>void In( ifstream& ); 
                          void In( FILE* );</code></pre>
    输出成绩<pre><code>void Out( ofstream& );
                void Out( FILE* );  </code></pre>
    显示成绩<pre><code>void print( ); </code></pre> 		
    求总评成绩<pre><code>void ComputeZP( ); </code></pre>
    求等级<pre><code>void ComputeDJ( );  </code></pre>
    读取总评成绩<pre><code>float GetZP( );  </code></pre>
    读取等级<pre><code>char GetDJ( ); </code></pre>
    等等  
5.  设计  
基本思想：  
    自顶向下、逐步细化  
主要功能：  
    (1)总控模块  
    功能：编制菜单，不断从菜单选择计算或查询功能执行，直到退出。  
    (2)计算  
    (3)查询～  
6.  实现  
    编程时要求每一个类建两个文件，即类的定义和实现文件。  
    注意包含相关的文件。
-----
### 二、模拟电信计费系统的设计与实现（25）
要求：

    （1）计费功能。根据存放在源数据文件中的通话记录和长途费率文件对每一条通话记录计算其通话费用，并将结果保存在费用文件中。其中：
        通话费的计算方法如下：
            通话费＝长途电话费＋本地电话费
            长途电话费＝费率（元/分钟）×通话时长（分钟)(通话时长不满1分钟的按1分钟计算)
            本地电话费为：3分钟以内0.5元，以后每3分钟递增0.2元。
    （2）话费查询。输入一个电话号码，从费用文件中统计该电话号码的所有本地话费、长途话费，并从用户文件中查找其用户名，最后在屏幕上显示：
        用户名  电话号码  本地话费  长途话费  话费总计
    （3）话单查询。输入一个电话号码，查询并在屏幕显示该用户的所有通话记录，格式为：
        用户名  主叫电话号码  被叫电话号码  通话时长
程序设计参考思路：
1.  本系统的输入输出文件  
    本系统的输入文件有三个：  
    (1) 源数据文件（hd.dat）  
    存放：主叫区号  主叫电话号码  被叫区号 被叫电话号码  通话时长（秒）
    每次通话作为一条记录，占源数据文件的一行。  
    每条记录中各数据之间以空格间隔，例如：  
    <pre><code>025  3491234  010  62320983  90</code></pre> 
    每个电话号码可以有多次通话记录。  
    如果主、被叫区号相同，则通话记录为本地通话记录；否则为长途通话记录。  
    (2) 长话费率文件（fl.dat）  
    存放：
    <pre><code>区号 费率  </code></pre> 
    例如：
    <pre><code>010  1.20</code></pre> 表示从本地打往区号为010的地区每分钟收费1.20元。  
    (3) 用户文件（yh.dat）  
    存放： <pre><code>电话号码   用户姓名  </code></pre> 
    例如：<pre><code> 3491234  张明    </code></pre> 
    本系统的输出文件有一个：  
    费用文件（fy.dat）  
    存放：<pre><code>主叫电话号码  通话类型  话费金额   </code></pre> 
    其中，通话类型表示本次通话是长途还是本地。  
2.  系统输入数据  
    fl.dat    有4条记录 
    <pre><code> 010   1.20   
    010   1.20   
    021   0.80 
    0571  1.00
    021   0.80</code></pre>
    yh.dat    有5条记录
    <pre><code>3491234  张明
    4927038  李小红
    7216340  王励
    3492200  赵强
    8120321  杨冬</code></pre>
    
    <pre><code>025  3491234  025  5319971   70       			
    025  4927038  010  62110045  236					
    025  7216340  025  4521009   310       			
    025  3491234  0571  2199516  100					
    025  8120321  021  81094532  50        					
    025  3491234  025  5319971   80 
    025  4927038  025  3491234   115       		   
    025  8120321  025  7216340   47					 
    025  7216340  010  62110045  93       			 
    025  3491234  010  62110045  792					
    025  4927038  0571  2199516  931       			 
    025  3491234  025  5319971   580					 
    025  4927038  025  3491234   358       
    025  8120321  021  81094532  197
    025  7216340  025  4521009   256       
    025  7216340  010  62110045  193
    025  3492200  025  4521009   320       
    025  3491234  025  5319971   270
    025  4927038  025  3491234   231       
    025  3492200  025  4927038   72</code></pre> 
3.  数据结构（可用C++实现）  
    三个类：<pre><code>话单（callist）、费用（charge）和用户（user）  </code></pre> 
    两个常量：  
    <pre><code>存放本地费率和递增量 </code></pre>  
    (1)话单类  
    数据成员：<pre><code>主叫区号、主叫电话号码、被叫区号、被叫电话号码、通话时长</code></pre>    
    数据类型  
    <pre><code>属性（私有、保护、公有）  </code></pre>  
    方法：  
    <pre><code>构造函数和析构函数  
    从源数据文件读入通话数据  
    显示一次通话数据  
    取主叫区号  
    取主叫电话号码	
    等等   </code></pre>  
    (2)费用类 —— 从话单类派生  
    数据成员： <pre><code> 通话类型、通话费用   </code></pre>  
    数据类型  
    <pre><code>属性（私有、保护、公有） </code></pre>   
    方法：<pre><code>构造函数和析构函数 
	        从费用文件读入费用数据 
		    向费用文件输出数据 
		    屏幕显示费用 
		    求通话费用 
		    求通话类型 
		    取（返回）通话类型 
		    取通话费用
            等等   </code></pre>  
    (3)用户类  
    数据成员：<pre><code>姓名、电话号码 </code></pre>   
    数据类型  
    <pre><code>属性（私有、保护、公有）  </code></pre>  
    方法：<pre><code>设置用户的电话号码
    查询用户名
    设置用户名
    查询用户的电话号码 
    显示用户名和电话号码 
    等等</code></pre>  
    4.  设计  
    基本思想：  
    自顶向下、逐步细化  
    主要功能：  
    (1)总控模块  
    (2)计算通话费用  
    定义一个话单对象，循环处理。  
    (3)费用查询  
    定义一个用户对象，根据电话号码查询用户信息  
    从“计算通话费用”模块生成的费用文件中，按通话类型分别统计某一电话号码的所有费用项。  可定义一个费用对象，循环累加。  
    在屏幕显示查询结果。  
    (4)话单查询  
    定义一个用户对象，根据电话号码查询用户信息  
    从源数据（话单）文件中，查询某一电话号码的所有通话清单。  
    在屏幕显示查询结果。  
    可定义一个话单对象，查询并显示。  
5.  实现  
(1)进行话费查询前，必须先进行费用计算。
* 可以先判断费用文件是否存在，若不存在，则调用计算通话费用模块后再查询；否则直接查询。
* 或者用一个全局变量实现——全局变量初值为0，调用计算通话费用模块后该全局变量置为1。当要查询通话费时，首先检查该全局变量的值。  
(2)为了统计话费方便，在费用文件中设一“通话类型”，可以用两个不同的字符表示本地和长途，如0表示本地，1表示长途。  
(3)编程时要求每一个类建两个文件，即类的定义和实现文件。  
(4)编程时注意包含相关的文件。