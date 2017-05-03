import pandas as pd
from matplotlib import pyplot as plt
import matplotlib as mpl
import numpy as np
from sklearn.pipeline import make_pipeline
from sklearn.ensemble import RandomForestClassifier
from sklearn.feature_selection import SelectKBest
from sklearn.cross_validation import StratifiedKFold
from sklearn.grid_search import GridSearchCV
from sklearn.ensemble.gradient_boosting import GradientBoostingClassifier
from sklearn.cross_validation import cross_val_score
from sklearn.ensemble import ExtraTreesClassifier
from sklearn.feature_selection import SelectFromModel


pd.options.display.max_columns = 100
pd.options.display.max_rows = 100

#mpl.style.use('ggplot')

data = pd.read_csv('train.csv')
#data.head()
#data.describe()

data['Age'].fillna(data['Age'].median(), inplace=True)
#data.describe()


###################################################
# Comment out each section to get a specific plot #
###################################################

# Sex
survived_sex = data[data['Survived']==True]['Sex'].value_counts()
dead_sex = data[data['Survived']==False]['Sex'].value_counts()
df = pd.DataFrame([survived_sex, dead_sex])
df.index = ['Survived', 'Dead']
df.plot(kind='bar', stacked=True, figsize=(13,8))
#plt.show()

# Age
figure = plt.figure(figsize=(13, 8))
plt.hist([data[data['Survived']==True]['Age'], data[data['Survived']==False]['Age']],
            stacked=True, color=['g', 'r'], bins=30, label=['Survived', 'Dead'])
plt.xlabel('Age')
plt.ylabel('Number of passengers')
plt.legend()
#plt.show()

# Fare
figure = plt.figure(figsize=(13,8))
plt.hist([data[data['Survived']==1]['Fare'],data[data['Survived']==0]['Fare']],
            stacked=True, color = ['g','r'], bins = 30,label = ['Survived','Dead'])
plt.xlabel('Fare')
plt.ylabel('Number of passengers')
plt.legend()
#plt.show()

# Age and Fare
plt.figure(figsize=(13,8))
ax = plt.subplot()
ax.scatter(data[data['Survived']==1]['Age'],data[data['Survived']==1]['Fare'],
            c='green',s=40)
ax.scatter(data[data['Survived']==0]['Age'],data[data['Survived']==0]['Fare'],
            c='red',s=40)
ax.set_xlabel('Age')
ax.set_ylabel('Fare')
ax.legend(('survived','dead'),scatterpoints=1,loc='upper right',fontsize=15)
#plt.show()

# Pclass
ax = plt.subplot()
ax.set_ylabel('Average fare')
data.groupby('Pclass').mean()['Fare'].plot(kind='bar',figsize=(13,8), ax = ax)
#plt.show()

# Embarked
survived_embark = data[data['Survived']==1]['Embarked'].value_counts()
dead_embark = data[data['Survived']==0]['Embarked'].value_counts()
df = pd.DataFrame([survived_embark,dead_embark])
df.index = ['Survived','Dead']
df.plot(kind='bar',stacked=True, figsize=(13,8))
plt.show()
