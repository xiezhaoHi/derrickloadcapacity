#pragma once


enum gWordLabelsNamesOne_enum
{
	gWordLabelsNamesOne_bgbh,//"报告编号"
	gWordLabelsNamesOne_wtf,//"委托方",
	gWordLabelsNamesOne_ypmc,//"样品名称",
	gWordLabelsNamesOne_ggxh,//"规格型号",
	gWordLabelsNamesOne_cplb,//"测评类别",
	gWordLabelsNamesOne_bgbh2,//"报告编号2"
	gWordLabelsNamesOne_ypmc2,//"样品名称2",
	gWordLabelsNamesOne_ggxh2,//"规格型号2",
	gWordLabelsNamesOne_wtfdz,//"委托方地址",
	gWordLabelsNamesOne_sb,//"商标",
	gWordLabelsNamesOne_xsdw,//"销售单位",
	gWordLabelsNamesOne_scrq,//生产日期
	gWordLabelsNamesOne_sydw,//"使用单位",
	gWordLabelsNamesOne_ccbh,//"出厂编号",
	gWordLabelsNamesOne_sydd,//"收样地点",
	gWordLabelsNamesOne_ypsl,//"样品数量",
	gWordLabelsNamesOne_ypztms,//"样品状态描述",
	gWordLabelsNamesOne_ypbsfs,//"样品标识方式",
	gWordLabelsNamesOne_ypbh,//"样品编号",
	gWordLabelsNamesOne_dyrq,//"到样日期",
	gWordLabelsNamesOne_wtflxr,//"委托方联系人",
	gWordLabelsNamesOne_cprq,//"测评日期",
	gWordLabelsNamesOne_cpdd,//"测评地点",
	gWordLabelsNamesOne_hjtj,//"环境条件",
	gWordLabelsNamesOne_cpsb,//"测评设备",
	gWordLabelsNamesOne_dqsjcznl,//"当前实际承载能力",
	gWordLabelsNamesOne_lx,//"轮系",
	gWordLabelsNamesOne_zdczd,//"最大钩载的",
	gWordLabelsNamesOne_jjpw,//"井架评为",
	gWordLabelsNamesOne_sjzdgzw,//"设计最大钩载为",
	gWordLabelsNamesOne_hls,//"滑轮数",
	gWordLabelsNamesOne_ym,//页眉
	gWordLabelsNamesOne_max
};

//word模板相应的标签名字
const char* gWordLabelsNamesOne[] = { "报告编号",
"委托方",
"样品名称",
"规格型号",
"测评类别",
"报告编号2",
"样品名称2",
"规格型号2",
"委托方地址",
"商标",
"销售单位",
"生产日期",
"使用单位",
"出厂编号",
"收样地点",
"样品数量",
"样品状态描述",
"样品标识方式",
"样品编号",
"到样日期",
"委托方联系人",
"测评日期",
"测评地点",
"环境条件",
"测评设备",
"当前实际承载能力",
"轮系",
"最大钩载的",
"井架评为",
"设计最大钩载为",
"滑轮数",
"页眉",
nullptr };


enum gWordLabelsNamesTwo_enum
{
	gWordLabelsNamesTwo_tczc,//"天车总成",
	gWordLabelsNamesTwo_fzhlzc,//"辅助滑轮总成",
	gWordLabelsNamesTwo_tcl,//"天车梁",
	gWordLabelsNamesTwo_jjdt,//"井架大腿",
	gWordLabelsNamesTwo_hljhxlj,//"横拉筋和斜拉筋",
	gWordLabelsNamesTwo_ect,//"二层台",
	gWordLabelsNamesTwo_tz,//"梯子",
	gWordLabelsNamesTwo_qszzhsszz,//"起升装置和伸缩装置",
	gWordLabelsNamesTwo_sjzzsssqbjj,//"锁紧装置伸缩式轻便井架",
	gWordLabelsNamesTwo_bsxt,//"绷绳系统",
	gWordLabelsNamesTwo_szjgj,//"栓装结构件",
	gWordLabelsNamesTwo_ssgdqjzz,//死绳国定器及支座",
	gWordLabelsNamesTwo_dz,//底座",
	gWordLabelsNamesTwo_jyqkzy,//校验情况摘要"
	gWordLabelsNamesTwo_cpfx, //测评分析
	gWordLabelsNamesTwo_max
};

//标签名类型的 多组标签名称
const  char* gWordLabelsNamesTwo[] = { "天车总成",
"辅助滑轮总成",
"天车梁",
"井架大腿",
"横拉筋和斜拉筋",
"二层台",
"梯子",
"起升装置和伸缩装置",
"锁紧装置伸缩式轻便井架",
"绷绳系统",
"栓装结构件",
"死绳国定器及支座",
"底座",
"校验情况摘要" ,"测评分析", nullptr };

//combox 索引
enum combox_enum
{
	combox_one,
	combox_two,
	combox_three,
	combox_four,//空项
	combox_max
};
QString gcomboxIndexs[combox_max] = { QStringLiteral("-"),QStringLiteral("√"),QStringLiteral("无"),QStringLiteral("") };


//计算数据填充
enum gWordJssjLabelsNames_enum
{
	gWordJssjLabelsNames_cdbz1, //"测点布置1"
	gWordJssjLabelsNames_cdbz2,//"测点布置2"
	gWordJssjLabelsNames_scsj1,//"实测数据1",
	gWordJssjLabelsNames_scsj2,//"实测数据2",
	gWordJssjLabelsNames_max
};
const  char* gWordJssjLabelsNames[] =
{
	"测点布置1",
	"测点布置2",
	"实测数据1",
	"实测数据2",
	nullptr
};


