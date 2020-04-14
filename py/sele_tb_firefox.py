import time
import random
from selenium import webdriver
from selenium.webdriver import ActionChains
from selenium.webdriver.common.proxy import *  #代理设置
import os
import re
#有可能会弹出验证码
#没有展示出来
q='小米'#关键字
usr_pswd=open('/home/tyx/xx.txt','r').read()#用户文件
usr_pswd=usr_pswd.split('#',1)
usr= usr_pswd[0]
pswd= usr_pswd[1]
print(usr+'\n'+pswd)
myProxy = '127.0.0.1:8080'#代理配置
proxy = Proxy({
  'proxyType': ProxyType.MANUAL, 
  'httpProxy': myProxy, 
  'ftpProxy': myProxy, 
  'sslProxy': myProxy, 
  'noProxy': ''
 })
class Flag():
  proxy=0
  noimage=0
  headless=0
  def __init__(self,proxy=0,noimage=0,headless=0):
    self.proxy=proxy
    self.noimage=noimage
    self.headless=headless
  def flags(self,proxy=0,noimage=0,headless=0):
    self.proxy=proxy
    self.noimage=noimage
    self.headless=headless
  def proxy(self):
    return self.proxy
  def proxy(self,value):
    self.proxy=value
  def noimage(self):
    return self.noimage
  def noimage(self,value):
    self.image=value
  def headless(self):
    return self.headless
  def headless(self,value):
    self.headless=value

class Cfg():
  flag=''
  options=''
  profile=''
  store=[]
  price=[]
  address=[]
  link=[]
  def __init__(self,proxy=0,noimage=0,headless=0):
    self.flag=Flag(proxy,noimage,headless)
    self.options=webdriver.FirefoxOptions()
    self.profile=webdriver.FirefoxProfile()
  def options_add(self, value):
    self.options.add_argument(value)
  def options_add_headless(self):
    if self.flag.headless is 1:
      self.options_add('-headless')#无界面模式
      print('无界面模式')
    else:print('界面模式')
  def profile_set(self,key,value):
    self.profile.set_preference(key,value)
  def profile_set_proxy(self,value):
    if self.flag.proxy is 1:#打开代理
      self.profile.set_proxy(proxy)
      print('代理'+str(proxy.httpProxy))
    else:print('未使用代理')
  def profile_set_noimage(self):
    if self.flag.noimage is 1:
      self.profile_set('permissions.default.image',2)
      print('无图模式')
    else:print('加载图片')
  def flag_proxy(self,value):
    self.flag.proxy=value
  def get_pasl(self,tp,ta,ts,tl):
    for i in range(tp.__len__()):
      self.price.append(tp[i].text)
      self.address.append(ta[i].text)
      self.store.append(ts[i].text)
      self.link.append(tl[i].get_attribute('href'))
  def save_pasl(self):#写入文件
    if os.path.isfile('1.txt') is False:
      open('1.txt','w+').close()
    with open('1.txt','a') as f:
      f.write(str(self.price)+'\n')
      f.write(str(self.address)+'\n')
      f.write(str(self.store)+'\n')
      f.write(str(self.link)+'\n')
  def show_pasl(self):#展示
    pass


def driver_get_pasl():
  global driver
  global cfg
  tp=driver.find_elements_by_css_selector('div>strong')#价格
  ta=driver.find_elements_by_css_selector('div.location')#地址
  ts=driver.find_elements_by_css_selector('span.dsrs+span')
  tl=driver.find_elements_by_css_selector('a.J_ItemPicA')
  cfg.get_pasl(tp,ta,ts,tl)#暂存
  return tl.__len__()

def driver_next_click():
  global driver
  driver.find_element_by_css_selector('[trace=srp_bottom_pagedown]').click()
  time.sleep(1)

cfg=Cfg(0,1,1)#代理、无图、无界面
cfg.profile_set_noimage()
cfg.profile_set_proxy(proxy)
cfg.options_add_headless()
try:
  driver = webdriver.Firefox( options=cfg.options,firefox_profile=cfg.profile)#定义浏览器
  driver.get('https://login.taobao.com/member/login.jhtml?spm=a21bo.2017.754894437.1.64a711d9vo0gj2&f=top&redirectURL=https%3A%2F%2Fwww.taobao.com%2F')

  driver.find_element_by_xpath('//*[@id="fm-login-id"]').send_keys(usr)
  driver.find_element_by_xpath('//*[@id="fm-login-password"]').send_keys(pswd)
  driver.find_element_by_xpath('/html/body/div/div[2]/div[3]/div/div[1]/div/div[2]/div/form/div[4]/button').click()
  time.sleep(5)
  driver.find_element_by_xpath('//*[@id="q"]').send_keys(q)
  driver.find_element_by_xpath('/html/body/div[2]/div/div/div[2]/div/div[1]/div[2]/form/div[1]').click()
  time.sleep(0.3)
  page=driver.find_element_by_css_selector('.total').text
  page=int(re.search('\d+',page).group())
  page=3
  print('page is '+str(page))
  #解析部分
  num=0
  for i in range(page):
    num=num+driver_get_pasl()
    driver_next_click()#下一页按钮
    cfg.save_pasl()
    print(num)
  driver.quit()
except:
  print('error')
  driver.quit()
# for i in range(1,49):
#   tp=driver.find_elements_by_xpath('/html/body/div[1]/div[2]/div[3]/div[1]/div[21]/div/div/div[1]/div['+str(i)+']/div[2]/div[1]/div[1]/strong')
#   ts=driver.find_elements_by_xpath('/html/body/div[1]/div[2]/div[3]/div[1]/div[21]/div/div/div[1]/div['+str(i)+']/div[2]/div[3]/div[1]/a/span[2]')
#   ta=driver.find_elements_by_xpath('/html/body/div[1]/div[2]/div[3]/div[1]/div[21]/div/div/div[1]/div['+str(i)+']/div[2]/div[3]/div[2]')
#   tl=driver.find_elements_by_xpath('/html/body/div[1]/div[2]/div[3]/div[1]/div[21]/div/div/div[1]/div['+str(i)+']/div[2]/div[2]')
#   tl=tl.find_element_by_name('herf')
#   price.append(tp[0].text)
#   store.append(ts[0].text)
#   address.append(ta[0].text)
#   link.append()
# driver.maximize_window()  # 窗口最大化
# driver.implicitly_wait(3)
# driver.find_element_by_id('J_Quick2Static').click()
# time.sleep(random.random()) # 随机休眠0-1秒
# # 输入账号密码 淘宝登陆框的input name是变化的，通过查找input控件应该更好
##TPL_username
##TPL_password
# browser.find_element_by_name('fm-login-id').send_keys(usr)
# browser.find_element_by_name('fm-login-password').send_keys(pswd)
# time.sleep(random.random())
# # 模拟滑动
# getcheck = driver.find_element_by_id('nc_1_n1z')
# ActionChains(driver).click_and_hold(on_element=getcheck).perform()
# ActionChains(driver).move_to_element_with_offset(to_element=getcheck, xoffset=120, yoffset=2).perform()
# time.sleep(0.1)
# ActionChains(driver).move_to_element_with_offset(to_element=getcheck, xoffset=120, yoffset=2).perform()
# time.sleep(0.3)
# ActionChains(driver).move_to_element_with_offset(to_element=getcheck, xoffset=120, yoffset=2).perform()
# time.sleep(0.9)
# # 模拟点击
# driver.find_element_by_id('J_SubmitStatic').click()
# driver.close()

