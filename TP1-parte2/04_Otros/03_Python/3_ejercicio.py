import pandas as pd
import threading as th
import os

semaphore = th.Semaphore(1)
arr_preferences = []


def thread_function(user_id, user_df):
    favorite_type = user_df.groupby('type')['type'].count().idxmax()
    favorite_genre = user_df.groupby('genre')['genre'].count().idxmax()
    total = user_df.count()['user_id']
    user_name = user_df['user_name'].unique()[0]
    different_genres = len(user_df['genre'].unique())
    with semaphore:
        arr_preferences.append({
            'user_id': int(user_id),
            'user_name': user_name,
            'favorite_genre': favorite_genre,
            'favorite_type': favorite_type,
            'total': int(total),
            'different_genres': int(different_genres)})


def main():
    path_file = os.path.dirname(os.path.abspath(__file__))
    path_csv = os.path.join(path_file, 'visualizaciones.csv')
    path_result = os.path.join(path_file, 'preferences.json')
    df = pd.read_csv(path_csv)
    users = df['user_id'].unique()
    threads = []
    for user in users:
        user_df = df[df['user_id'] == user]
        thread = th.Thread(target=thread_function, args=(user, user_df))
        thread.start()
        threads.append(thread)

    for thread in threads:
        thread.join()

    df_preferences = pd.DataFrame(arr_preferences, columns=['user_id', 'user_name', 'favorite_genre', 'favorite_type', 'total', 'different_genres'])
    df_preferences.to_json(path_result, orient='records', lines=False, force_ascii=False, indent=4)


if __name__ == "__main__":
    main()
