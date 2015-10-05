# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <codecell>

# import seaborn
import numpy as np
import pandas as pd
from patsy import dmatrices, dmatrix
from pandas import Series, DataFrame
import matplotlib.pyplot as plt
%pylab inline
import time
import sklearn
from sklearn.decomposition import PCA
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import Lars
from sklearn import neighbors
from sklearn import gaussian_process
from sklearn.cross_validation import KFold
from sklearn.grid_search import GridSearchCV
import scipy.stats as stats
import scipy
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from sklearn import neighbors, datasets
from mpl_toolkits.mplot3d import Axes3D

# <codecell>

dfInitTrain = pd.read_csv('/root/code/gs/data/risk_Initial_Training_Data.csv', header=None)

# <codecell>

dfInitTest = pd.read_csv('/root/code/gs/data/Initial_Test_Data.csv', header=None)

# <codecell>

dfInitTrain.describe()

# <codecell>

dfInitTest.describe()

# <codecell>

dfpre = pd.read_csv('/root/code/gs/data/preproces.csv', header=None)

# <codecell>

dfpre.describe()

# <codecell>

dftest = pd.read_csv('/root/code/gs/data/pre_testdata.csv', header=None)

# <codecell>

dftest.drop([3, 4], axis=1, inplace=True)

# <codecell>

dfpre.drop([3, 4], axis=1, inplace=True)

# <codecell>

trainData = np.array(dfpre, dtype='float')
testData = np.array(dftest, dtype='float')

# <codecell>

df_final_train = pd.read_csv('/root/Downloads/pre_final_train.csv', header=None)

# <codecell>

df_final_train.notnull().all(axis=1).sum()

# <codecell>

df_final_train

# <codecell>

df_final_test = pd.read_csv('/root/Downloads/pre_final_test.csv', header=None)

# <codecell>

df_final_test

# <markdowncell>

# ## TEST DATA

# <codecell>

final_train = np.array(df_final_train.drop([3, 4], axis=1, inplace=False))
final_test = np.array(df_final_test.drop([3, 4], axis=1, inplace=False))
print final_train.shape, final_test.shape

# <codecell>

ftrain_x = final_train[:, :-1]
ftrain_y = final_train[:, -1]

# <codecell>

ftrain_x.shape

# <codecell>

import time
import sklearn
from sklearn.decomposition import PCA
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import Lars
from sklearn import neighbors
from sklearn import gaussian_process
from sklearn.cross_validation import KFold
from sklearn.grid_search import GridSearchCV

# <codecell>

from sklearn import ensemble

# <codecell>

clf = ensemble.RandomForestClassifier(n_estimators=500, oob_score=True, bootstrap=True)
clf.fit(ftrain_x, ftrain_y)
print clf.oob_score_

# <codecell>

a = clf.predict(final_test)

# <codecell>

clf_train = ensemble.RandomForestClassifier(n_estimators=500, oob_score=True)
clf_train.fit(train_x, train_y)
clf_train.oob_score_

# <codecell>

clf_combined = ensemble.RandomForestClassifier(n_estimators=1100, oob_score=True)
clf_combined.fit(combined_x, combined_y)
clf_combined.oob_score_

# <codecell>

final_test

# <codecell>

a = clf_combined.predict(final_test)
output = zip(final_test[:, 0], a)

# <codecell>

combined_x = np.zeros((train_x.shape[0] + ftrain_x.shape[0], 17))
combined_y = np.zeros((train_y.shape[0]+ftrain_y.shape[0],))

# <codecell>

combined_x[:8287, :] = train_x
combined_x[8287:, :] = ftrain_x
combined_y[:8287 ] = train_y
combined_y[8287:] = ftrain_y

# <codecell>

import csv
with open('test.csv', 'w') as fp:
    a = csv.writer(fp, delimiter=',')
    a.writerows(output)

# <markdowncell>

# ## TRAINING DATA!

# <codecell>

NT = 7000

# <codecell>

ind = [i for i in xrange(trainData.shape[0])]
numpy.random.shuffle(ind)
ind_train = ind[:NT]
ind_valid = ind[NT+1:]
print len(ind), len(ind_train), len(ind_valid)

# <codecell>

train_x = trainData[:, :-1]
train_y = trainData[:, -1]
# valid_x = trainData[ind_valid, :-1]
# valid_y = trainData[ind_valid, -1]
test_x = testData

# <codecell>

print trainData.shape, train_x.shape, train_y.shape
print valid_x.shape, valid_y.shape
print test_x.shape

# <codecell>

F = train_x.shape[1]
ind_val = [1, 2]
ind_cat = [x for x in xrange(F) if x not in ind_val]
print F, ind_val, ind_cat

# <codecell>

train_x.shape

# <codecell>

combined

# <codecell>

n_neighbors = 15
# we create an instance of Neighbours Classifier and fit the data.

# clf = neighbors.KNeighborsClassifier(n_neighbors, weights='distance', metric='pyfunc', func=knnDist)
clf = neighbors.KNeighborsClassifier(n_neighbors, weights='distance')
clf.fit(train_x, train_y)

print clf.score(valid_x, valid_y)

# <codecell>

sklearn_pca = PCA(n_components=17)
pca_train = sklearn_pca.fit_transform(train_x)
R = np.dot(train_x.T, train_x)
w, a = scipy.linalg.eig(R)
w = abs(w)
eigval = sort(w)[::-1]
eigtot = sum(eigval)
print eigval[0] / eigtot

# <codecell>

sklearn_pca = PCA(n_components=17)
pca_valid = sklearn_pca.fit_transform(valid_x)
R = np.dot(valid_x.T, valid_x)
w, a = scipy.linalg.eig(R)
w = abs(w)
eigval = sort(w)[::-1]
eigtot = sum(eigval)
print eigval[0] / eigtot

# <codecell>

pca_valid.shape

# <codecell>

n_neighbors = 15

# clf = neighbors.KNeighborsClassifier(n_neighbors, weights='distance', metric='pyfunc', func=knnDist)
clf = neighbors.KNeighborsClassifier(n_neighbors, weights='distance')
clf.fit(pca_train, train_y)

print clf.score(pca_valid, valid_y)

# <codecell>

ensemble.RandomForestClassifier()

