# Hotel mangement project

## توضیحات اولیه درباره این پروژه

این برنامه به شکل شی محور و به زبان سی پلاس پلاس نوشته شده است و برای هر موجودیت یک کلاس جداگانه در نظر گرفته ایم  که در ادامه به توضیح بخش های مهم آن می پردازیم:
  در این پروژه ۷ کلاس داریم که شامل کلاس های زیر میباشد :
کلاس parser ٬
کلاس server٬
کلاس client٬
کلاس room٬
کلاس user ٬
کلاس reservation٬
کلاس network٬

## توضیحات کلاس ها :

### Parser کلاس

در این کلاس توابعی وجود دارند که برای parse کردن فایل های جیسون استفاده میشوند و در هر دو کلاس سرور و کلاینت مورد استفاده قرار میگیرند .
تابع اصلی این فایل parsJson است :

[![image](https://www.linkpicture.com/q/parserJson.png)](https://www.linkpicture.com/view.php?img=LPic6413028e7484f1816288767)

این تابع یک فایل جیسون را به عنوان ورودی دریافت میکند و یک داده ساختار map
از string
به vector 
حاوی تمام key ها 
و value ها
به عنوان خروجی برمیگرداند.
در این تابع vector ها 
برای ذخیره داده های لیست های فایل جیسون مورد استفاده قرار میگیرند و در صورتی که هر key فقط 
یک value داشته باشد 
آن value در خانه اول ذخیره میشود .

### کلاس User

ابن کلاس اطلاعات مربوط به هر user را ذخیره میکند
یک vector به
نام users از این کلاس داریم که اطلاعات تمام کاربران در آن ذخیره شده است.
فایل user.hpp به شکل زیر است :

[![image](https://www.linkpicture.com/q/parserJson.png)](https://www.linkpicture.com/view.php?img=LPic6413028e7484f1816288767)

این فایل اطلاعات کاربر را در قالب فیلدهای private ذخیره میکند .
این کلاس یک constructor 
و تعدادی تابع دیگر دارد که مهم ترین آن ها را شرح میدهیم . برای مثال تابع isValid چک میکند که 
آیا username داده شده قابل قبول هست یا نه .
تابعی مانند isAdimn بررسی میکند که فردی که دسترسی میخواهد ادمین است یا کاربر عادی.
تابع reduceMoney مقدار مشخص شده ای را از کیف پول فرد برمیدارد .
تابع edit میتواند داده های وارد شده برای کاربران را در صورت نیاز تغییر دهد.
یک تابع پرکاربرد این کلاس که برای کلاس های دیگر هم به طور جداگانه تعریف شده است to_string نام دارد که اطلاعاتی که مدنظر بوده را
به شکل string در آورده و برای چاپ کردن و نمایش دادن اطلاعات کاربران مورد استفاده قرار میگیرد.

[![image](https://www.linkpicture.com/q/Usercpp1.png)](https://www.linkpicture.com/view.php?img=LPic64130cf04b72f941790233)
[![image](https://www.linkpicture.com/q/Usercpp2.png)](https://www.linkpicture.com/view.php?img=LPic64130cf04b72f941790233)

### کلاس Reservation

این کلاس اطلاعات رزرو هر فرد را ذخیره میکند . فیلد های پرایوت آن شامل تعداد تخت ها و تاریخ آغاز و پایان رزرو و یک پوینتز از کلاس کاربر است .
فایل reservation.hpp به شکل زیر است :

[![image](https://www.linkpicture.com/q/Reservhpp_1.png)](https://www.linkpicture.com/view.php?img=LPic6413240e68a7f1823775595)

این کلاس یک constructor دارد 
و شامل دو تابع getStartInterval()
و getEndInterval()
است که این توابع تاریخ شروع و پایان رزرو را از فرمت string
به یک عدد int تبدیل میکنند.

[![image](https://www.linkpicture.com/q/Reservcpp_1.png)](https://www.linkpicture.com/view.php?img=LPic6413240e68a7f1823775595)

### کلاس Room

این کلاس اطلاعات هر اتاق را ذخیره میکند . فیلدهای پرایوت آن شامل وضعیت اتاق(پر یا خالی بودن آن)٫ قیمت اتاق٫حداکثر ظرفیت آن و ظرفیتی که از اتاق پر شده و شماره آن میباشد.

فایل room.hpp به صورت زیر است :

[![image](https://www.linkpicture.com/q/Roomhpp.png)](https://www.linkpicture.com/view.php?img=LPic64133b14f3ea51144886599)

این کلاس  یک constructor دارد و
مهم ترین تابع این کلاس hasConfict است .
این تابع یک موجودیت از کلاس reservation به عنوان ورودی دریافت میکند و 
بررسی میکند که در یک بازه زمانی خاص چند نفر یک تخت را رزرو نکرده باشند که این کار را با کمک توابع interval که در 
کلاس reservation تعریف شده بود و انجام میدهد 
و در صورتی که تداخل زمانی برای رزرو یک تخت وجود داشت این تابع true برمیگرداند.

تابع findNumOfreserveById تعداد رزروهایی که یک نفر 
با id داده شده انجام داده را بر میگرداند و 
این کار را با استفاده از اطلاعات موجود در vector<reservation> users انجام میدهد .

تابع removeReservationById رزرو های فرد را با استفاده 
از id او حذف میکند.

[![image](https://www.linkpicture.com/q/Roomcpp1.png)](https://www.linkpicture.com/view.php?img=LPic64133b14f3ea51144886599)

[![image](https://www.linkpicture.com/q/Roomcpp2.png)](https://www.linkpicture.com/view.php?img=LPic64133b14f3ea51144886599)

### کلاس client 

این فایل شامل ۳ تابع است که وظیفه اصلی آن ها وصل شدن به سرور ٫ فرستادن دستور و دریافت پاسخ و نمایش آن است . 

تابع connectServer شماره پورتی که باید به آن متصل شود را دریافت کرده و برای آن درخواست میفرستد.
در صورت قبول شدن درخواست fd مربوط به آن را برمیگرداند .

تابع writeLog زمان حال سیستم را دریافت کرده و با استفاده از ورودی خود 
که curr_log است اطلاعات لازم را در 
فایل log.txt 
که در فولدر configuration است مینویسد .

[![image](https://www.linkpicture.com/q/client1.png)](https://www.linkpicture.com/view.php?img=LPic641342e3b879c1799715608)

تابع main 
فایل config.json را خوانده و پورت داده و دستور را دریافت میکند و با 
فراخوانی تابع connectServer برای آن درخواست ارسال میکند.
سپس مینواند در یک حلقه بی نهایت دستور ارسال و دریافت کند و با استفاده ار دستور ctrl+c از حلقه خارج شود .
در پایان حلقه و در صورت خروج از آن fd یسته میشود.

[![image](https://www.linkpicture.com/q/client2.png)](https://www.linkpicture.com/view.php?img=LPic641342e3b879c1799715608)

[![image](https://www.linkpicture.com/q/client3.png)](https://www.linkpicture.com/view.php?img=LPic641342e3b879c1799715608)


### کلاس server 

این کلاس به صورت کلی وظیفه بالا آوردن سرور٫ listen کردن و اجرای دستور کلاینت ها را به عهده دارد .
فایل server.hpp به صورت زیر است :

[![image](https://www.linkpicture.com/q/serverhpp.png)](https://www.linkpicture.com/view.php?img=LPic64134c9d447391850347168)

تابع setUpServer یک سوکت ایجاد میکند . 
در این تابع عملیات ساخت سوکت bind کردن آن 
و listen کردن روی آن انجام میشود.

[![image](https://www.linkpicture.com/q/setupserver.png)](https://www.linkpicture.com/view.php?img=LPic64134d11d82ec975450604)

تابع acceptClient برای قبول کردن یک کاربر که میخواهد به سوکت متصل شود مورد استفاده قرار میگیرد.

[![image](https://www.linkpicture.com/q/accceptthing.png)](https://www.linkpicture.com/view.php?img=LPic641356e401011276453938)

تابع run وظیفه پاسخگویی به درخواست های کاربران را دارد .

[![image](https://www.linkpicture.com/q/قعد.png)](https://www.linkpicture.com/view.php?img=LPic6413581b6031e1118534929)

[![image](https://www.linkpicture.com/q/قعد۲.png)](https://www.linkpicture.com/view.php?img=LPic6413581b6031e1118534929)

تابع commandHandler وظیفه برای اجرای تمام دستورات و نمایش صفحه اصلی استفاده میشود .
این تابع در ابتدا دستورات را یر حسب تعداد ورودی جدا میکند و مقدار هر ورودی را مشخص میکند و سپس هر کدام از دستورات را نمایش داده و کارهای لازم را انجام میدهد .

[![image](https://www.linkpicture.com/q/قعد۲.png)](https://www.linkpicture.com/view.php?img=LPic6413581b6031e1118534929)

[![image](https://www.linkpicture.com/q/قعد۲.png)](https://www.linkpicture.com/view.php?img=LPic6413581b6031e1118534929)

[![image](https://www.linkpicture.com/q/قعد۲.png)](https://www.linkpicture.com/view.php?img=LPic6413581b6031e1118534929)

[![image](https://www.linkpicture.com/q/قعد۲.png)](https://www.linkpicture.com/view.php?img=LPic6413581b6031e1118534929)

[![image](https://www.linkpicture.com/q/قعد۲.png)](https://www.linkpicture.com/view.php?img=LPic6413581b6031e1118534929)

[![image](https://www.linkpicture.com/q/قعد۲.png)](https://www.linkpicture.com/view.php?img=LPic6413581b6031e1118534929)

[![image](https://www.linkpicture.com/q/قعد۲.png)](https://www.linkpicture.com/view.php?img=LPic6413581b6031e1118534929)




تابع convertCOnfig برای تبدیل 
کردن map بدست آمده از 
تابع parser 
به فیلد های یوزر است.

[![image](https://www.linkpicture.com/q/convertConfig.png)](https://www.linkpicture.com/view.php?img=LPic64135ba1084ba393989122)


### کلاس network 

این فایل تنها شامل یک تابع main است که وظیفه 
دریافت map ساخته شده 
توسط parseJson و 
بالا آوردن سرور با استفاده از آن دارد .

[![image](https://www.linkpicture.com/q/Network_2.png)](https://www.linkpicture.com/view.php?img=LPic64135d7ced86b905615975)




