import os
import pandas as pd
from pandas.errors import EmptyDataError

def list_files(directory):
    files = []
    for filename in os.listdir(directory):
        path = os.path.join(directory, filename)
        if os.path.isfile(path):
            files.append(filename)
    return files

DATASETS = ["dblp", "eu2005", "hprd", "human", "patents", "wordnet", "yeast", "youtube"]

to_group = 'vertex_count'
to_drop = ['vertex_id', 'vertex_count', 'edge_count', 'diameter', 'density']
to_drop.remove(to_group)

orbits = ['o$_{'+str(i)+"}$" for i in range(15)]
to_exclude = ['o$_{0}$', 'o$_{2}$', 'o$_{7}$']
reduced_orbits = [x for x in orbits if x not in to_exclude]


full_gf_df = pd.read_csv("GF.csv")
cross_product = [(x, y) for x in full_gf_df[to_group].unique() for y in reduced_orbits]

orbit_df = pd.read_csv("orbit-summary.csv")
orbit_df.columns = ['vertex_id'] + orbits + ['pattern','data']
orbit_df = orbit_df.drop(['o$_{0}$','o$_{2}$','o$_{7}$'], axis=1)

i = 1
for DATASET in DATASETS:
  gf_df = full_gf_df[full_gf_df["data"] == DATASET]
  gf_df = gf_df[['pattern', 'vertex_count', 'edge_count', 'diameter', 'density']]

  append_df = orbit_df[orbit_df["data"] == DATASET]
  append_df = append_df.drop(["data"], axis=1)

  f_df = append_df.groupby(['pattern']).sum().reset_index().merge(gf_df, how="inner").fillna(0).drop(['pattern'], axis=1).groupby([to_group]).mean().reset_index().drop(to_drop, axis=1)
  melted_f_df = pd.melt(f_df, id_vars=[to_group])
  melted_f_df.columns = ["Vertex Count", "Orbit", "Count"]
  for product in cross_product:
    combination_exists = (melted_f_df['Vertex Count'] == product[0]) & (melted_f_df['Orbit'] == product[1])
    if not combination_exists.any():
        melted_f_df = pd.concat([melted_f_df, pd.DataFrame([{'Vertex Count': product[0], 'Orbit': product[1], 'Count': np.nan}])], ignore_index=True)

  print(melted_df)
  break
