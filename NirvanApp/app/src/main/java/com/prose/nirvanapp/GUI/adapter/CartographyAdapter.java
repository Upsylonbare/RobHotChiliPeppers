package com.prose.nirvanapp.GUI.adapter;
import android.content.Context;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;


import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.prose.nirvanapp.R;
import com.prose.nirvanapp.CartoManager.Carto;

import java.util.ArrayList;


public class CartographyAdapter extends RecyclerView.Adapter<CartographyAdapter.ViewHolder>
{

    private Context context;
    private ArrayList<Carto> data = new ArrayList<>();

    public CartographyAdapter (Context context, ArrayList<Carto> data ){
        this.data = data;
        this.context = context;
    }
    @Override
    public CartographyAdapter.ViewHolder onCreateViewHolder( ViewGroup parent, int viewType) {

        LayoutInflater layoutInflater = LayoutInflater.from(parent.getContext());
        View view = layoutInflater.inflate(R.layout.adapter_carto,parent,false);
        ViewHolder viewHolder = new ViewHolder(view);
        return viewHolder;
    }

    @Override
    public void onBindViewHolder(CartographyAdapter.ViewHolder holder, int position) {

        holder.textView.setText(data.get(position).getName());

    }

    @Override
    public int getItemCount()
    {
        return data.size();
    }

    public class ViewHolder extends RecyclerView.ViewHolder
    {
        TextView textView;
        public ViewHolder(@NonNull View itemView)
        {
            super(itemView);
            textView = itemView.findViewById(R.id.carto_title);
        }

    }



}
