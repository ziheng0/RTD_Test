#### How to compile
1. Prerequisites
Make sure current python version is 3.x.
2. To install corresponding components according to docs/requirements.txt 
```bash
cd RTD_Test
python -m venv venv
source venv/bin/activate
pip install <python modules>
```
3. Compile
```bash
make html
```

#### How to test
1. Preview 
After compiling is success, below html file will be generated. You can directly open it by brownser.
docs/build/html/index.html

2. Deploy
After code is commited, system will compiling it aotumatically. And you will find it from here https://quecopen.readthedocs.io/en/latest/index.html