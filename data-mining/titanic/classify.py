# matplotlib alternate display for ssh x11
import matplotlib as mpl
#mpl.use('Agg')
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns
from sklearn.svm import SVC
from sklearn.neural_network import MLPClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.neighbors import KNeighborsClassifier

# load data
t_train = pd.read_csv("train.csv")
t_test  = pd.read_csv("test.csv")

# eliminate useless attributes, keep passengerid for future elimination
t_train = t_train.drop(['Name','Ticket','Cabin','Embarked'], axis = 1)
t_test  = t_test.drop(['Name','Ticket','Cabin','Embarked'], axis = 1)

# convert nominal to numeric
mapping = {'male': 0, 'female': 1}
t_train = t_train.replace({'Sex': mapping})
t_test  = t_test.replace({'Sex': mapping})

# attempt to fill in missing data
#t_train['Age'] = t_train['Age'].fillna(t_train['Age'].median())
#t_test['Age'] = t_test['Age'].fillna(t_test['Age'].median())
#t_test['Fare'] = t_test['Fare'].fillna(t_test['Fare'].mean())
t_train['Age'] = t_train['Age'].fillna(0)
t_test['Age'] = t_test['Age'].fillna(0)
t_test['Fare'] = t_test['Fare'].fillna(0)

# drop passengerid
t_train = t_train.drop(['PassengerId'], axis = 1)
t_test_X = t_test.drop(['PassengerId'], axis = 1)

# features and labels
t_train_X = t_train.drop('Survived', axis = 1)
t_train_y = t_train['Survived']

# train the model
#mod = RandomForestClassifier(
#        n_estimators = 20, criterion = 'entropy',
#        max_depth = None, max_features = 4, n_jobs = -1)
#mod = KNeighborsClassifier(
#        n_neighbors = 7, weights = 'distance', p = 3, n_jobs = -1)
#mod = MLPClassifier(
#        hidden_layer_sizes = (200, 3), activation = 'logistic',
#        max_iter = 500, tol = 1e-05)
mod = SVC(kernel = 'rbf', degree = 4, tol = 0.0001)
mod.fit(t_train_X, t_train_y)

# output score of training and predictions
score = mod.score(t_train_X, t_train_y)
preds = mod.predict(t_test_X)
print("Score: {}".format(score))

# output predictions to submission file
passid = pd.Series(t_test['PassengerId'], name = 'PassengerId')
predic = pd.Series(preds, name = 'Survived')
output = pd.concat([passid, predic], axis = 1)
output.to_csv('gender_submission.csv', index = False)

