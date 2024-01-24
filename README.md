# c
[gcc](https://github.com/bmox/c/raw/main/gcc.zip) <br>
[C](https://github.com/bmox/c/raw/main/C.zip) <br>
[linux](https://github.com/bmox/raw/main/linux.zip) <br>

```
import requests
import shutil
url = "https://github.com/bmox/c/raw/main/gcc.zip"
path="gcc.zip"
response = requests.get(url)
with open(path , 'wb') as file:
  file.write(response.content)
shutil.unpack_archive(path, "./")
```
```
wget https://github.com/bmox/c/raw/main/gcc.zip
```
```
unzip gcc.zip
```
