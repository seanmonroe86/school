import pandas as pd
import numpy as np
from sklearn.svm import SVC
from sklearn.neural_network import MLPClassifier
from sklearn.model_selection import RandomizedSearchCV
from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import RandomForestClassifier

params_RFC = [
        {'n_estimators': 10, 'criterion': 'gini', 'max_depth': None, 'max_features': 'auto', 'n_jobs': -1},
        {'n_estimators': 20, 'criterion': 'gini', 'max_depth': None, 'max_features': 'auto', 'n_jobs': -1},
        {'n_estimators': 10, 'criterion': 'gini', 'max_depth': 4, 'max_features': 'auto', 'n_jobs': -1},
        {'n_estimators': 20, 'criterion': 'gini', 'max_depth': 4, 'max_features': 'auto', 'n_jobs': -1},
        {'n_estimators': 10, 'criterion': 'gini', 'max_depth': None, 'max_features': 4, 'n_jobs': -1},
        {'n_estimators': 20, 'criterion': 'gini', 'max_depth': None, 'max_features': 4, 'n_jobs': -1},
        {'n_estimators': 10, 'criterion': 'gini', 'max_depth': 4, 'max_features': 4, 'n_jobs': -1},
        {'n_estimators': 20, 'criterion': 'gini', 'max_depth': 4, 'max_features': 4, 'n_jobs': -1},
        {'n_estimators': 10, 'criterion': 'entropy', 'max_depth': None, 'max_features': 'auto', 'n_jobs': -1},
        {'n_estimators': 20, 'criterion': 'entropy', 'max_depth': None, 'max_features': 'auto', 'n_jobs': -1},
        {'n_estimators': 10, 'criterion': 'entropy', 'max_depth': 4, 'max_features': 'auto', 'n_jobs': -1},
        {'n_estimators': 20, 'criterion': 'entropy', 'max_depth': 4, 'max_features': 'auto', 'n_jobs': -1},
        {'n_estimators': 10, 'criterion': 'entropy', 'max_depth': None, 'max_features': 4, 'n_jobs': -1},
        {'n_estimators': 20, 'criterion': 'entropy', 'max_depth': None, 'max_features': 4, 'n_jobs': -1},
        {'n_estimators': 10, 'criterion': 'entropy', 'max_depth': 4, 'max_features': 4, 'n_jobs': -1},
        {'n_estimators': 20, 'criterion': 'entropy', 'max_depth': 4, 'max_features': 4, 'n_jobs': -1}
        ]

params_KNN = [
        {'n_neighbors': 2, 'weights': 'uniform', 'p': 1, 'n_jobs': -1},
        {'n_neighbors': 2, 'weights': 'distance', 'p': 1, 'n_jobs': -1},
        {'n_neighbors': 2, 'weights': 'uniform', 'p': 2, 'n_jobs': -1},
        {'n_neighbors': 2, 'weights': 'distance', 'p': 2, 'n_jobs': -1},
        {'n_neighbors': 2, 'weights': 'uniform', 'p': 3, 'n_jobs': -1},
        {'n_neighbors': 2, 'weights': 'distance', 'p': 3, 'n_jobs': -1},
        {'n_neighbors': 3, 'weights': 'uniform', 'p': 1, 'n_jobs': -1},
        {'n_neighbors': 3, 'weights': 'distance', 'p': 1, 'n_jobs': -1},
        {'n_neighbors': 3, 'weights': 'uniform', 'p': 2, 'n_jobs': -1},
        {'n_neighbors': 3, 'weights': 'distance', 'p': 2, 'n_jobs': -1},
        {'n_neighbors': 3, 'weights': 'uniform', 'p': 3, 'n_jobs': -1},
        {'n_neighbors': 3, 'weights': 'distance', 'p': 3, 'n_jobs': -1},
        {'n_neighbors': 5, 'weights': 'uniform', 'p': 1, 'n_jobs': -1},
        {'n_neighbors': 5, 'weights': 'distance', 'p': 1, 'n_jobs': -1},
        {'n_neighbors': 5, 'weights': 'uniform', 'p': 2, 'n_jobs': -1},
        {'n_neighbors': 5, 'weights': 'distance', 'p': 2, 'n_jobs': -1},
        {'n_neighbors': 5, 'weights': 'uniform', 'p': 3, 'n_jobs': -1},
        {'n_neighbors': 5, 'weights': 'distance', 'p': 3, 'n_jobs': -1},
        {'n_neighbors': 7, 'weights': 'uniform', 'p': 1, 'n_jobs': -1},
        {'n_neighbors': 7, 'weights': 'distance', 'p': 1, 'n_jobs': -1},
        {'n_neighbors': 7, 'weights': 'uniform', 'p': 2, 'n_jobs': -1},
        {'n_neighbors': 7, 'weights': 'distance', 'p': 2, 'n_jobs': -1},
        {'n_neighbors': 7, 'weights': 'uniform', 'p': 3, 'n_jobs': -1},
        {'n_neighbors': 7, 'weights': 'distance', 'p': 3, 'n_jobs': -1},
        {'n_neighbors': 10, 'weights': 'uniform', 'p': 1, 'n_jobs': -1},
        {'n_neighbors': 10, 'weights': 'distance', 'p': 1, 'n_jobs': -1},
        {'n_neighbors': 10, 'weights': 'uniform', 'p': 2, 'n_jobs': -1},
        {'n_neighbors': 10, 'weights': 'distance', 'p': 2, 'n_jobs': -1},
        {'n_neighbors': 10, 'weights': 'uniform', 'p': 3, 'n_jobs': -1},
        {'n_neighbors': 10, 'weights': 'distance', 'p': 3, 'n_jobs': -1}
        ]

params_MLP = [
        {'hidden_layer_sizes': (100, 3), 'activation': 'logistic', 'max_iter': 500, 'tol': 1e-5},
        {'hidden_layer_sizes': (100, 3), 'activation': 'relu', 'max_iter': 500, 'tol': 1e-5},
        {'hidden_layer_sizes': (100, 5), 'activation': 'logistic', 'max_iter': 500, 'tol': 1e-5},
        {'hidden_layer_sizes': (100, 5), 'activation': 'relu', 'max_iter': 500, 'tol': 1e-5},
        {'hidden_layer_sizes': (200, 3), 'activation': 'logistic', 'max_iter': 500, 'tol': 1e-5},
        {'hidden_layer_sizes': (200, 3), 'activation': 'relu', 'max_iter': 500, 'tol': 1e-5},
        {'hidden_layer_sizes': (200, 5), 'activation': 'logistic', 'max_iter': 500, 'tol': 1e-5},
        {'hidden_layer_sizes': (200, 5), 'activation': 'relu', 'max_iter': 500, 'tol': 1e-5},
        {'hidden_layer_sizes': (300, 3), 'activation': 'logistic', 'max_iter': 500, 'tol': 1e-5},
        {'hidden_layer_sizes': (300, 3), 'activation': 'relu', 'max_iter': 500, 'tol': 1e-5}
        ]

params_SVC = [
        {'kernel': 'rbf', 'degree': 2, 'tol': 1e-5},
        {'kernel': 'rbf', 'degree': 3, 'tol': 1e-5},
        {'kernel': 'rbf', 'degree': 4, 'tol': 1e-5},
        {'kernel': 'rbf', 'degree': 2, 'tol': 1e-4},
        {'kernel': 'rbf', 'degree': 3, 'tol': 1e-4},
        {'kernel': 'rbf', 'degree': 4, 'tol': 1e-4},
        {'kernel': 'rbf', 'degree': 2, 'tol': 1e-3},
        {'kernel': 'rbf', 'degree': 3, 'tol': 1e-3},
        {'kernel': 'rbf', 'degree': 4, 'tol': 1e-3},
        {'kernel': 'rbf', 'degree': 2, 'tol': 1e-2},
        {'kernel': 'rbf', 'degree': 3, 'tol': 1e-2},
        {'kernel': 'rbf', 'degree': 4, 'tol': 1e-2}
        ]

t_train = pd.read_csv("train.csv")
t_test  = pd.read_csv("test.csv")

t_train = t_train.drop(['Name','Ticket','Cabin','Embarked','Age'], axis = 1)
t_test  = t_test.drop(['Name','Ticket','Cabin','Embarked','Age'], axis = 1)

mapping = {'male': 0, 'female': 1}
t_train = t_train.replace({'Sex': mapping})
t_test  = t_test.replace({'Sex': mapping})
t_test = t_test.fillna(0)

t_train  = t_train.drop(['PassengerId'], axis = 1)
t_test_X = t_test.drop(['PassengerId'], axis = 1)
t_train_X = t_train.drop('Survived', axis = 1)
t_train_y = t_train['Survived']

scores_RFC = []
scores_KNN = []
scores_MLP = []
scores_SVC = []

out = open('output.txt', 'w')

string = "\n\n\nRandom Forest-----------------------------------------------------"
print(string)
out.write(string)
for params in params_RFC:
    rfc = RandomForestClassifier(**params)
    rfc.fit(t_train_X, t_train_y)
    score = rfc.score(t_train_X, t_train_y)
    scores_RFC.append((score, params))
    string = 'Score: {}\nParams:{}\n'.format(score, params)
    print(string)
    out.write(string)

string = "\n\n\nK-Nearest-Neighbor------------------------------------------------"
print(string)
out.write(string)
for params in params_KNN:
    knn = KNeighborsClassifier(**params)
    knn.fit(t_train_X, t_train_y)
    score = knn.score(t_train_X, t_train_y)
    scores_KNN.append((score, params))
    string = 'Score: {}\nParams:{}\n'.format(score, params)
    print(string)
    out.write(string)

string = "\n\n\nNeural Network----------------------------------------------------"
print(string)
out.write(string)
for params in params_MLP:
    mlp = MLPClassifier(**params)
    mlp.fit(t_train_X, t_train_y)
    score = mlp.score(t_train_X, t_train_y)
    scores_MLP.append((score, params))
    string = 'Score: {}\nParams:{}\n'.format(score, params)
    print(string)
    out.write(string)

string = "\n\n\nSupport Vector Machine--------------------------------------------"
print(string)
out.write(string)
for params in params_SVC:
    svc = SVC(**params)
    svc.fit(t_train_X, t_train_y)
    score = svc.score(t_train_X, t_train_y)
    scores_SVC.append((score, params))
    string = 'Score: {}\nParams:{}\n'.format(score, params)
    print(string)
    out.write(string)

#max_score = [0,]
#for score, params in scores_RFC:
#    if score > max_score[0]:
#        max_score[0] = score
#        max_score[1] = params
#


out.close()
